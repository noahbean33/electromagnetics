
static char help[] = "1D FDTD simulation program.\n\n";

#include <petscdm.h>
#include <petscdmda.h>
#include <petscvec.h>
#include <petscviewer.h>

// instead of separate E and H arrays using array of structs holding both values
typedef struct {
	PetscScalar e, h;
} FieldNode;

int
main(int argc, char **argv)
{
	PetscErrorCode ierr;
#define E(x)                                                                                                           \
	do {                                                                                                           \
		ierr = x;                                                                                              \
		CHKERRQ(ierr);                                                                                         \
	} while (0)

	PetscMPIInt rank;
	PetscInt    N	 = 200;		    // domain size
	PetscInt    SN	 = 50;		    // source node index
	PetscInt    Tmax = 250, Tsnap = 50; // time options
	PetscScalar imp0 = 377;		    // free space impedance
	Vec	    fg, f;		    // field vectors

	ierr = PetscInitialize(&argc, &argv, NULL, help);
	if (ierr) {
		return ierr;
	}
	E(MPI_Comm_rank(PETSC_COMM_WORLD, &rank));

	// get cli options
	E(PetscOptionsGetInt(NULL, NULL, "-N", &N, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-SN", &SN, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-Tmax", &Tmax, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-Tsnap", &Tsnap, NULL));

	// create output file
	PetscViewer output;
	E(PetscViewerASCIIOpen(PETSC_COMM_WORLD, "output.csv", &output));
	E(PetscViewerSetType(output, PETSCVIEWERASCII));
	E(PetscViewerPushFormat(output, PETSC_VIEWER_ASCII_COMMON));

	// create calculation domain
	// This object is responsible for synchronization between distributed
	// electric and magnetic field arrays and their local parts.
	// This includes setting up
	// vector ghosts (https://docs.petsc.org/en/latest/manual/vec/#local-ghosted-work-vectors).
	DM domain;
	E(DMDACreate1d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED, N, 2, 1, NULL, &domain));
	E(DMSetUp(domain));
	E(DMDASetFieldName(domain, 0, "e"));
	E(DMDASetFieldName(domain, 1, "h"));

	// create electric and magnetic field vectors
	E(DMCreateGlobalVector(domain, &fg));
	E(VecZeroEntries(fg));

	E(DMCreateLocalVector(domain, &f));

	E(VecAssemblyBegin(fg));
	E(VecAssemblyBegin(f));

	E(VecAssemblyEnd(fg));
	E(VecAssemblyEnd(f));

	// When using DMDAVecGetArrayWrite we index vector with global index rather then local
	// Therefore, we need to get both size and start of the vector
	// These values includes ghost points on both ends of the chunk
	PetscInt size, start, end;
	E(DMDAGetGhostCorners(domain, &start, NULL, NULL, &size, NULL, NULL));
	end = start + size;

	// main loop
	for (PetscInt t = 0; t < Tmax; t++) {
		// load data from global arrays to local array parts
		E(DMGlobalToLocal(domain, fg, INSERT_VALUES, f));

		FieldNode *farr;
		E(DMDAVecGetArrayWrite(domain, f, &farr));

		// first H field value of the chunk was not calculated in the adjoined array
		// so we need to recalculate the ghost node
		// do not need to recalculate ghost for the leftmost chunk
		if (start != -1) {
			farr[start].h += (farr[start + 1].e - farr[start].e) / imp0;
		}
		// save previous timestep value of the neighbor
		if (end-1 == N) {
			farr[end-1].h = farr[end-2].h;
		}
		for (PetscInt i = start + 1; i < end-1; i++) {
			farr[i].h += (farr[i + 1].e - farr[i].e) / imp0;
			if (i == 0) {
				// save previous timestep value of the neighbor
				farr[i].e = farr[i+1].e;
			} else {
				farr[i].e += (farr[i].h - farr[i - 1].h) * imp0;
			}
		}
		farr[end-1].e += (farr[end-1].h - farr[end - 2].h) * imp0;

		// additive field source
		// assert that node owns this part of vector before writing to it
		if ((start <= SN) && (end >= SN)) {
			farr[SN].e += exp(-(t - 30.) * (t - 30.) / 100.);
		}

		E(DMDAVecRestoreArrayWrite(domain, f, &farr));

		// synchronize global array with calculated values
		E(DMLocalToGlobal(domain, f, INSERT_VALUES, fg));

		if ((t + 1) % Tsnap == 0) {
			// dump electric field into the text file
			// this is not straightforward because data is scattered across MPI nodes
			E(DMDAVecGetArrayRead(domain, f, &farr));
			E(PetscViewerASCIIPushSynchronized(output));
			PetscInt i = start + 1;
			if (i == 0) {
				E(PetscViewerASCIISynchronizedPrintf(output, "%f", farr[0].e));
				i++;
			}
			for (; i < end-1; i++) {
				E(PetscViewerASCIISynchronizedPrintf(output, ",%f", farr[i].e));
			}
			E(PetscViewerFlush(output));
			E(PetscViewerASCIIPopSynchronized(output));
			if (start <= 0) {
				E(PetscViewerASCIIPrintf(output, "\n"));
				E(PetscViewerFlush(output));
			}
			E(DMDAVecRestoreArrayRead(domain, f, &farr));
		}
	}

	// destroy everything
	E(VecDestroy(&f));
	E(VecDestroy(&fg));
	E(DMDestroy(&domain));
	E(PetscViewerDestroy(&output));
	E(PetscFinalize());
	return ierr;
}

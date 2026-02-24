
static char help[] = "1D FDTD simulation program.\n\n";

#include <petscdm.h>
#include <petscdmda.h>
#include <petscvec.h>
#include <petscviewer.h>

// instead of separate E and H arrays using array of structs holding both values and loss coefficients
// for electric and magnetic fields
// \(Loss_E = \frac{\sigma_E \Delta t}{2 \epsilon}\)
// \(C_E^E = \frac{1-Loss_E}{1+Loss_E}\)
// \(C_E^H = \frac{\frac{\eta_0}{\epsilon_r}S_c}{1+Loss_E}\)
// \(Loss_H = \frac{\sigma_H \Delta t}{2 \mu}\)
// \(C_H^E = \frac{1-Loss_H}{1+Loss_H}\)
// \(C_H^H = \frac{\frac{\eta_0}{\epsilon_r}S_c}{1+Loss_H}\)
typedef struct {
	PetscScalar e, h;
	PetscScalar cee, ceh;
	PetscScalar che, chh;
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
	PetscInt    EPSsplit = 100;	    // node at which permittivity changes from EPSl to EPSr
	PetscScalar EPSl = 1.0, EPSr = 9.0; // permittivity at the left and at the right parts of the domain
	PetscInt    LOSSsplit = 150;	    // node at which lossy region begins
	PetscScalar Loss = 0.01;	    // loss in the lossy region
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
	E(PetscOptionsGetInt(NULL, NULL, "-EPSsplit", &EPSsplit, NULL));
	E(PetscOptionsGetScalar(NULL, NULL, "-EPSl", &EPSl, NULL));
	E(PetscOptionsGetScalar(NULL, NULL, "-EPSr", &EPSr, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-LOSSsplit", &LOSSsplit, NULL));
	E(PetscOptionsGetScalar(NULL, NULL, "-Loss", &Loss, NULL));

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
	// We calculate degree of freedom instead of hardcoding it
	E(DMDACreate1d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED,
		       N, sizeof(FieldNode) / sizeof(PetscScalar), 1,
		       NULL, &domain));
	E(DMSetUp(domain));

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

	// initialize calculation coefficients
	E(DMGlobalToLocal(domain, fg, INSERT_VALUES, f));
	FieldNode *farr;
	E(DMDAVecGetArrayWrite(domain, f, &farr));
	for (PetscInt i = start; i < end; i++) {
		if (i <= LOSSsplit) {
			farr[i].cee = 1.0;
			farr[i].ceh = imp0;
			farr[i].chh = 1.0;
			farr[i].che = 1.0 / imp0;
		} else {
			farr[i].cee = (1.0 - Loss) / (1.0 + Loss);
			farr[i].ceh = imp0 / (1.0 + Loss);
			farr[i].chh = (1.0 - Loss) / (1.0 + Loss);
			farr[i].che = 1.0 / imp0 / (1.0 + Loss);
		}
		if (i <= EPSsplit) {
			farr[i].ceh /= EPSl;
		} else {
			farr[i].ceh /= EPSr;
		}
	}
	E(DMDAVecRestoreArrayWrite(domain, f, &farr));
	// write data to global vectors
	E(DMLocalToGlobal(domain, f, INSERT_VALUES, fg));

	// main loop
	for (PetscInt t = 0; t < Tmax; t++) {
		// load data from global arrays to local array parts
		E(DMGlobalToLocal(domain, fg, INSERT_VALUES, f));

		E(DMDAVecGetArrayWrite(domain, f, &farr));

		// first H field value of the chunk was not calculated in the adjoined array
		// so we need to recalculate the ghost node
		// do not need to recalculate ghost for the leftmost chunk
		if (start != -1) {
			farr[start].h = farr[start].chh * farr[start].h +
				farr[start].che * (farr[start + 1].e - farr[start].e);
		}
		for (PetscInt i = start + 1; i < end-1; i++) {
			farr[i].h = farr[i].chh * farr[i].h +
				farr[i].che * (farr[i + 1].e - farr[i].e);
			if (i == SN) {
				// update H field to TFSF boundary
				float exp_arg = t - 30.;
				farr[i].h -= exp(-exp_arg * exp_arg / 100.) / imp0;
			}
			if (i == 0) {
				// save previous timestep value of the neighbor
				farr[i].e = farr[i+1].e;
			} else {
				// account for relative permittivity
				farr[i].e = farr[i].cee * farr[i].e + farr[i].ceh * (farr[i].h - farr[i - 1].h);
			}
			if (i == SN+1) {
				// update E field to TFSF boundary
				float exp_arg = t + 0.5 - (-0.5) - 30.;
				farr[i].e += exp(-exp_arg * exp_arg / 100.);
			}
		}
		farr[end-1].e = farr[end-1].cee * farr[end-1].e + farr[end-1].ceh * (farr[end-1].h - farr[end - 2].h);

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

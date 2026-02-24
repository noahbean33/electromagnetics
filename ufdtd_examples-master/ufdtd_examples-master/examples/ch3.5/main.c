
static char help[] = "1D FDTD simulation program.\n\n";

#include <petscdm.h>
#include <petscdmda.h>
#include <petscvec.h>
#include <petscviewer.h>

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
	PetscInt    Tmax = 250, Tsnap = 50; // time options
	PetscScalar imp0 = 377;		    // free space impedance
	Vec	    eg, hg;		    // global field vectors
	Vec	    e, h;		    // local field vectors

	ierr = PetscInitialize(&argc, &argv, NULL, help);
	if (ierr) {
		return ierr;
	}
	E(MPI_Comm_rank(PETSC_COMM_WORLD, &rank));

	// get cli options
	E(PetscOptionsGetInt(NULL, NULL, "-N", &N, NULL));
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
	E(DMDACreate1d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED, N, 1, 1, NULL, &domain));
	E(DMSetUp(domain));

	// create electric and magnetic field vectors
	E(DMCreateGlobalVector(domain, &eg));
	E(VecZeroEntries(eg));
	E(VecDuplicate(eg, &hg));

	E(DMCreateLocalVector(domain, &e));
	E(VecDuplicate(e, &h));

	E(VecAssemblyBegin(eg));
	E(VecAssemblyBegin(hg));
	E(VecAssemblyBegin(e));
	E(VecAssemblyBegin(h));

	E(VecAssemblyEnd(eg));
	E(VecAssemblyEnd(hg));
	E(VecAssemblyEnd(e));
	E(VecAssemblyEnd(h));

	PetscInt size;
	E(VecGetSize(e, &size));

	// main loop
	for (PetscInt t = 0; t < Tmax; t++) {
		// load data from global arrays to local array parts
		E(DMGlobalToLocal(domain, eg, INSERT_VALUES, e));
		E(DMGlobalToLocal(domain, hg, INSERT_VALUES, h));

		PetscScalar *earr, *harr;
		E(VecGetArray(e, &earr));
		E(VecGetArray(h, &harr));

		// Note that array indexes 0 and size-1 are actually ghost values
		// They will be automatically copied from the adjoined arrays
		for (PetscInt i = 0; i < size - 1; i++) {
			harr[i] += (earr[i + 1] - earr[i]) / imp0;
		}
		for (PetscInt i = 1; i < size; i++) {
			earr[i] += (harr[i] - harr[i - 1]) * imp0;
		}

		// Hardwired source
		if (rank == 0) {
			earr[1] = exp(-(t - 30.) * (t - 30.) / 100.);
		}

		E(VecRestoreArray(e, &earr));
		E(VecRestoreArray(h, &harr));

		// synchronize global array with calculated values
		E(DMLocalToGlobal(domain, e, INSERT_VALUES, eg));
		E(DMLocalToGlobal(domain, h, INSERT_VALUES, hg));

		if ((t + 1) % Tsnap == 0) {
			// dump electric field into the text file
			// this is not straightforward because data is scattered across MPI nodes
			E(VecGetArrayRead(e, (const PetscScalar **) &earr));
			E(PetscViewerASCIIPushSynchronized(output));
			PetscInt i = 1;
			if (rank == 0) {
				E(PetscViewerASCIISynchronizedPrintf(output, "%f", earr[1]));
				i++;
			}
			for (; i < size - 1; i++) {
				E(PetscViewerASCIISynchronizedPrintf(output, ",%f", earr[i]));
			}
			E(PetscViewerFlush(output));
			E(PetscViewerASCIIPopSynchronized(output));
			if (rank == 0) {
				E(PetscViewerASCIIPrintf(output, "\n"));
				E(PetscViewerFlush(output));
			}
			E(VecRestoreArrayRead(e, (const PetscScalar **) &earr));
		}
	}

	// destroy everything
	E(VecDestroy(&eg));
	E(VecDestroy(&hg));
	E(VecDestroy(&e));
	E(VecDestroy(&h));
	E(DMDestroy(&domain));
	E(PetscViewerDestroy(&output));

	return PetscFinalize();
}

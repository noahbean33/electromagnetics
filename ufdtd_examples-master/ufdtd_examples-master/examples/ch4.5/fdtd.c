#include "fdtd.h"

#include <stdlib.h>

Config *config = NULL;
Grid *  g = NULL;

PetscErrorCode
fdtdInit(int argc, char **argv)
{
	ierr = PetscInitialize(&argc, &argv, NULL, help);
	if (ierr) {
		exit(ierr);
	}
	atexit((void (*)(void)) PetscFinalize);
	return MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
}

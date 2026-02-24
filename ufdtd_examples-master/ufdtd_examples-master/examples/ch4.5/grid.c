#include <stdlib.h>

#include "fdtd.h"

void gridFree() {
	if (g->domain != NULL) {
		DMDestroy(&g->domain);
		VecDestroy(&g->f);
		VecDestroy(&g->fg);
	}
	if (g != NULL) {
		free(g);
		g = NULL;
	}
}

PetscErrorCode gridInitBegin() {
	if (g != NULL) {
		PetscErrorPrintf("Grid is already allocated\n");
		return(1);
	}
	if (config == NULL) {
		PetscErrorPrintf("Config is not initialized\n");
		return(1);
	}
	g = calloc(1, sizeof(Grid));

	E(DMDACreate1d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED,
		       config->sizeX, sizeof(FieldNode) / sizeof(PetscScalar),
		       1, NULL, &g->domain));
	E(DMSetUp(g->domain));

	E(DMCreateGlobalVector(g->domain, &g->fg));
	E(VecZeroEntries(g->fg));

	E(DMCreateLocalVector(g->domain, &g->f));

	E(VecAssemblyBegin(g->fg));
	E(VecAssemblyBegin(g->f));
	atexit(gridFree);
	return 0;
}

PetscErrorCode gridInitEnd() {
	if ((g == NULL) || (g->domain == NULL)) {
		PetscErrorPrintf("Grid is already allocated\n");
		return(1);
	}
	E(VecAssemblyEnd(g->fg));
	E(VecAssemblyEnd(g->f));
	E(DMDAGetGhostCorners(g->domain, &g->start, NULL, NULL, &g->size, NULL, NULL));
	g->end = g->start + g->size;
	return 0;
}

PetscErrorCode gridInit() {
	E(gridInitBegin());
	E(gridInitEnd());
	return 0;
}

PetscErrorCode gridSetConst() {
	if ((g == NULL) || (g->domain == NULL)) {
		PetscErrorPrintf("Grid is not initialized\n");
		return(1);
	}
	E(DMGlobalToLocal(g->domain, g->fg, INSERT_VALUES, g->f));
	FieldNode *farr;
	E(DMDAVecGetArrayWrite(g->domain, g->f, &farr));
	for (PetscInt i = g->start; i < g->end; i++) {
		if (i <= config->lossSplit) {
			farr[i].ceze = 1.0;
			farr[i].cezh = IMP0;
			farr[i].chyh = 1.0;
			farr[i].chye = 1.0 / IMP0;
		} else {
			farr[i].ceze = (1.0 - config->loss) / (1.0 + config->loss);
			farr[i].cezh = IMP0 / (1.0 + config->loss);
			farr[i].chyh = (1.0 - config->loss) / (1.0 + config->loss);
			farr[i].chye = 1.0 / IMP0 / (1.0 + config->loss);
		}
		if (i <= config->epsSplit) {
			farr[i].cezh /= config->epsL;
		} else {
			farr[i].cezh /= config->epsR;
		}
	}
	E(DMDAVecRestoreArrayWrite(g->domain, g->f, &farr));
	E(DMLocalToGlobal(g->domain, g->f, INSERT_VALUES, g->fg));
	return 0;
}

PetscInt gridBoundaryIndex(Boundary b) {
	if ((g == NULL) || (g->domain == NULL)) {
		PetscErrorPrintf("Grid is not initialized\n");
		return(-1);
	}
	switch (b) {
	case Left: {
		return 0;
		break;
	}
	case Right: {
		return config->sizeX-1;
		break;
	}
	default:
		PetscErrorPrintf("Unknown boundary\n");
		return -1;
		break;
	}
}

PetscErrorCode gridWriteAccess() {
	if ((g == NULL) || (g->domain == NULL)) {
		PetscErrorPrintf("Grid is not initialized\n");
		return(1);
	}
	E(DMDAVecGetArrayRead(g->domain, g->f, &g->fieldArray));
}

PetscErrorCode gridWriteReturn() {
	if ((g == NULL) || (g->domain == NULL)) {
		PetscErrorPrintf("Grid is not initialized\n");
		return(1);
	}
	E(DMDAVecGetArrayRead(g->domain, g->f, &g->fieldArray));
}

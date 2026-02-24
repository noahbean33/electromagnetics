#include "fdtd.h"

static PetscViewer output;

void
snapshotFree()
{
	if (output != NULL) {
		PetscViewerDestroy(&output);
	}
}

PetscErrorCode
snapshotInit()
{
	if (output != NULL) {
		PetscErrorPrintf("snapshot is already initialized\n");
	}
	E(PetscViewerASCIIOpen(PETSC_COMM_WORLD, outFile, &output));
	E(PetscViewerSetType(output, PETSCVIEWERASCII));
	E(PetscViewerPushFormat(output, PETSC_VIEWER_ASCII_COMMON));
	atexit(snapshotFree);
	return 0;
}

PetscErrorCode
snapshot()
{
	if (g == NULL) {
		PetscErrorPrintf("Grid is not initialized\n");
	}
	FieldNode *farr;
	E(DMDAVecGetArrayRead(g->domain, g->f, &farr));
	E(PetscViewerASCIIPushSynchronized(output));
	PetscInt i = g->start + 1; // exclude ghost node
	if (i == 0) {
		E(PetscViewerASCIISynchronizedPrintf(output, "%f", farr[0].e));
		i++;
	}
	for (; i < g->end - 1; i++) {
		E(PetscViewerASCIISynchronizedPrintf(output, ",%f", farr[i].e));
	}
	E(PetscViewerFlush(output));
	E(PetscViewerASCIIPopSynchronized(output));
	if (g->start <= 0) {
		E(PetscViewerASCIIPrintf(output, "\n"));
		E(PetscViewerFlush(output));
	}
	E(DMDAVecGetArrayRead(g->domain, g->f, &farr));
	return 0;
}

/* PetscErrorCode */
/* snapshotMaybe() */
/* { */
/* 	if ((g->time + 1) % config->timeSnap == 0) { */
/* 		E(snapshot()); */
/* 	} */
/* 	return 0; */
/* } */

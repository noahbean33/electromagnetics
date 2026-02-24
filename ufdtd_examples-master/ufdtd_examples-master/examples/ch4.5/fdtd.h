#pragma once

#include <petscdmda.h>
#include <petscerror.h>
#include <stdlib.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static PetscScalar IMP0	     = 377.; // free space impedance
static char	   help[]    = "1D FDTD simulation program.\n\n";
static char	   outFile[] = "output.csv";

static PetscErrorCode ierr; // global error code
#define E(x)                                                                                                           \
	do {                                                                                                           \
		ierr = x;                                                                                              \
		CHKERRQ(ierr);                                                                                         \
	} while (0)

static PetscMPIInt rank; // current MPI rank

typedef struct {
	PetscScalar e, h;
	PetscScalar ceze, cezh;
	PetscScalar chye, chyh;
} FieldNode;

typedef struct {
	PetscInt    sizeX;     // size of computational domain
	PetscInt    sourceX;   // power source node
	PetscInt    maxTime;   // max time step
	PetscInt    timeSnap;  // time snap
	PetscInt    epsSplit;  // node at which permittivity changes from EPSl to EPSr
	PetscInt    lossSplit; // node at which lossy region begins
	PetscScalar cdtds;     // Courant number
	PetscScalar epsL;      // permittivity at the left part of the domain
	PetscScalar epsR;      // permittivity at the right part of the domain
	PetscScalar loss;      // loss in the lossy region
} Config;

typedef struct {
	Vec	   fieldGlobal;	     // global field vector
	Vec	   fieldLocal;	     // local field vector
	FieldNode *fieldArray;	     // local field array
	DM	   domain;	     // calculation domain
	PetscInt   size, start, end; // local vector
	PetscInt   time;	     // current time step
} Grid;

typedef enum {
	EField,
	HField,
} FieldPart;

typedef enum {
	Left,
	Right,
} Boundary;

extern Config *config; // global config
extern Grid *  g;      // global grid

#pragma GCC diagnostic pop

PetscErrorCode fdtdInit(int argc, char **argv);
PetscErrorCode configLoad();
PetscErrorCode gridInit();
PetscErrorCode gridInitBegin();
PetscErrorCode gridInitEnd();
PetscErrorCode snapshotInit();
PetscErrorCode snapshot();
PetscErrorCode snapshotMaybe();
PetscErrorCode gridSetConst();

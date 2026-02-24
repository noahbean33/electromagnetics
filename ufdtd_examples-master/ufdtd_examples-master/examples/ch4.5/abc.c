#include "fdtd.h"

PetscErrorCode
abcInit(void)
{
	return 0;
}

inline PetscErrorCode
abcSimple(FieldNode* f, FieldPart part, PetscInt boundaryIndex, PetscInt domainIndex)
{
	switch (part) {
	case EField: {
		f[boundaryIndex].e = f[domainIndex].e;
		break;
	}
	case HField: {
		f[boundaryIndex].h = f[domainIndex].h;
		break;
	}
	default:
		PetscErrorPrintf("Unknown field part\n");
		return 1;
		break;
	}
	return 0;
}

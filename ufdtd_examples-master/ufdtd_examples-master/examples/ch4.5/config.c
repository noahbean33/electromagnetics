#include "fdtd.h"

void
configFree()
{
	if (config != NULL) {
		free(config);
	}
}

void
configSetDefaults()
{
	config->sizeX	  = 200;
	config->sourceX	  = 50;
	config->maxTime	  = 250;
	config->timeSnap  = 20;
	config->epsSplit  = 100;
	config->lossSplit = 150;
	config->cdtds	  = 1.0;
	config->epsL	  = 1.0;
	config->epsR	  = 9.0;
	config->loss	  = 0.01;
}

PetscErrorCode
configLoad()
{
	if (config == NULL) {
		config = calloc(1, sizeof(Config));
		configSetDefaults();
		atexit(configFree);
	}
	E(PetscOptionsGetInt(NULL, NULL, "-sizeX", &config->sizeX, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-sourceX", &config->sourceX, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-maxTime", &config->maxTime, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-timeSnap", &config->timeSnap, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-epsSplit", &config->epsSplit, NULL));
	E(PetscOptionsGetInt(NULL, NULL, "-lossSplit", &config->lossSplit, NULL));
	E(PetscOptionsGetScalar(NULL, NULL, "-epsL", &config->epsL, NULL));
	E(PetscOptionsGetScalar(NULL, NULL, "-epsR", &config->epsR, NULL));
	E(PetscOptionsGetScalar(NULL, NULL, "-loss", &config->loss, NULL));
	return 0;
}

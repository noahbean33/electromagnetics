

#include <petscdm.h>
#include <petscdmda.h>
#include <petscvec.h>
#include <petscviewer.h>

#include "fdtd.h"

// instead of separate E and H arrays using array of structs holding both values and loss coefficients
// for electric and magnetic fields
// \(Loss_E = \frac{\sigma_E \Delta t}{2 \epsilon}\)
// \(C_E^E = \frac{1-Loss_E}{1+Loss_E}\)
// \(C_E^H = \frac{\frac{\eta_0}{\epsilon_r}S_c}{1+Loss_E}\)
// \(Loss_H = \frac{\sigma_H \Delta t}{2 \mu}\)
// \(C_H^E = \frac{1-Loss_H}{1+Loss_H}\)
// \(C_H^H = \frac{\frac{\eta_0}{\epsilon_r}S_c}{1+Loss_H}\)
// typedef struct {
// 	PetscScalar e, h;
// 	PetscScalar cee, ceh;
// 	PetscScalar che, chh;
// } FieldNode;

int
main(int argc, char **argv)
{
	E(fdtdInit(argc, argv));
	E(configLoad());
	E(snapshotInit());
	E(gridInit());
	E(gridSetConst());

	E(snapshotMaybe());

	// // main loop
	// for (PetscInt t = 0; t < Tmax; t++) {
	// 	// load data from global arrays to local array parts
	// 	E(DMGlobalToLocal(domain, fg, INSERT_VALUES, f));

	// 	E(DMDAVecGetArrayWrite(domain, f, &farr));

	// 	// first H field value of the chunk was not calculated in the adjoined array
	// 	// so we need to recalculate the ghost node
	// 	// do not need to recalculate ghost for the leftmost chunk
	// 	if (start != -1) {
	// 		farr[start].h = farr[start].chh * farr[start].h +
	// 			farr[start].che * (farr[start + 1].e - farr[start].e);
	// 	}
	// 	for (PetscInt i = start + 1; i < end-1; i++) {
	// 		farr[i].h = farr[i].chh * farr[i].h +
	// 			farr[i].che * (farr[i + 1].e - farr[i].e);
	// 		if (i == SN) {
	// 			// update H field to TFSF boundary
	// 			float exp_arg = t - 30.;
	// 			farr[i].h -= exp(-exp_arg * exp_arg / 100.) / imp0;
	// 		}
	// 		if (i == 0) {
	// 			// save previous timestep value of the neighbor
	// 			farr[i].e = farr[i+1].e;
	// 		} else {
	// 			// account for relative permittivity
	// 			farr[i].e = farr[i].cee * farr[i].e + farr[i].ceh * (farr[i].h - farr[i - 1].h);
	// 		}
	// 		if (i == SN+1) {
	// 			// update E field to TFSF boundary
	// 			float exp_arg = t + 0.5 - (-0.5) - 30.;
	// 			farr[i].e += exp(-exp_arg * exp_arg / 100.);
	// 		}
	// 	}
	// 	farr[end-1].e = farr[end-1].cee * farr[end-1].e + farr[end-1].ceh * (farr[end-1].h - farr[end - 2].h);

	// 	E(DMDAVecRestoreArrayWrite(domain, f, &farr));

	// 	// synchronize global array with calculated values
	// 	E(DMLocalToGlobal(domain, f, INSERT_VALUES, fg));

	// 	if ((t + 1) % Tsnap == 0) {
	// 		// dump electric field into the text file
	// 		// this is not straightforward because data is scattered across MPI nodes
	// 		E(DMDAVecGetArrayRead(domain, f, &farr));
	// 		E(PetscViewerASCIIPushSynchronized(output));
	// 		PetscInt i = start + 1;
	// 		if (i == 0) {
	// 			E(PetscViewerASCIISynchronizedPrintf(output, "%f", farr[0].e));
	// 			i++;
	// 		}
	// 		for (; i < end-1; i++) {
	// 			E(PetscViewerASCIISynchronizedPrintf(output, ",%f", farr[i].e));
	// 		}
	// 		E(PetscViewerFlush(output));
	// 		E(PetscViewerASCIIPopSynchronized(output));
	// 		if (start <= 0) {
	// 			E(PetscViewerASCIIPrintf(output, "\n"));
	// 			E(PetscViewerFlush(output));
	// 		}
	// 		E(DMDAVecGetArrayRead(domain, f, &farr));
	// 	}
	// }

	// // destroy everything
	// E(VecDestroy(&f));
	// E(VecDestroy(&fg));
	// return ierr;
	return 0;
}

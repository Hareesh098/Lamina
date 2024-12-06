#include <stdio.h>
#include <string.h>
#include "globalExtern.h"

void EvalProps() {
 real v, vv;
 virSum = 0.0;
 vSumX = 0.0; vSumY = 0.0; vSum = 0.0; 
 vvSum = 0.;
 int n;

 for (n = 1; n <= nAtom; n++) {
  vv = 0.;
  // Initialize v with a default value to avoid "uninitialized" warning.
  v = 0.0;
  // X direction velocity
  if (strcmp(solver, "Verlet") == 0) {
    v = vx[n];
  } else if (strcmp(solver, "LeapFrog") == 0) {
    v = vx[n] - 0.5 * deltaT * ax[n];
  }
   vSum += v;
   vv += Sqr(v);
   vSumX += v; 
   // Y direction velocity
   if (strcmp(solver, "Verlet") == 0) {
   v = vy[n];
   } else if (strcmp(solver, "LeapFrog") == 0) {
   v = vy[n] - 0.5 * deltaT * ay[n];
   }
   vSum += v;
   vSumY += v;
   vv += Sqr(v);
   vvSum += vv;
  }

  kinEnergy = 0.5 * vvSum / nAtom ;
  uSumPairPerAtom = uSumPair / nAtom ;
  BondEnergyPerAtom = TotalBondEnergy / nAtom  ;
  potEnergy = uSumPairPerAtom +  BondEnergyPerAtom ;
  totEnergy = kinEnergy + potEnergy;
  virSumxx = virSumPairxx  + virSumBondxx ;
  virSumyy = virSumPairyy  + virSumBondyy ;
  virSumxy = virSumPairxy  + virSumBondxy ;
  virSum = virSumPair + virSumBond;
  pressure = density * (vvSum + virSum) / (nAtom * NDIM);

}


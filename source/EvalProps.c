/*
 * This file is part of Lamina.
 *
 * Lamina is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lamina is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lamina. If not, see <https://www.gnu.org/licenses/>.

 Copyright (C) 2025 Harish Charan, University of Durham, UK

 */


#include <stdio.h>
#include <string.h>
#include "global.h"

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
  BondEnergyPerAtom = TotalBondEnergy / (0.5*nAtom); //Factor of 0.5 since each atom has one half the bond energy
  potEnergy = uSumPairPerAtom +  BondEnergyPerAtom ;
  totEnergy = kinEnergy + potEnergy;
  virSumxx = virSumPairxx  + virSumBondxx ;
  virSumyy = virSumPairyy  + virSumBondyy ;
  virSumxy = virSumPairxy  + virSumBondxy ;
  virSum = virSumPair + virSumBond;
  pressure = density * (vvSum + virSum) / (nAtom * NDIM);

}


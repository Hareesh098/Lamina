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

#include<stdio.h>
#include<stdlib.h>
#include"global.h"
void Close(){
  int n;
  free(rx);
  free(ry);
  free(vx);
  free(vy);
  free(ax);
  free(ay);
  free(fax);
  free(fay);
  free(cellList);

  free(atomID); free(atomType); free(atomRadius); free(atomMass);
  free(speed);
  free(atom1); free(atom2); free(BondID);
  free(BondType); free(kb); free(ro);
  free(ImageX); free(ImageY); free(rxUnwrap); free(ryUnwrap);
  free(atomIDInterface);
  free(PairID); free(Pairatom1); free(Pairatom2); 
  free(PairXij); free(PairYij);

  free(DeltaXijOld);
  free(DeltaYijOld);

  free(molID);
  
  for (n = 0; n <= nAtom; n++) {
   free(isBonded[n]);
   }
   free(isBonded);


  
  for(n = 0; n <= nAtom; n++) {
   free(DeltaXijOldPair[n]);
   free(DeltaYijOldPair[n]);
   }
    free(DeltaXijOldPair);
    free(DeltaYijOldPair);

  for (n = 0; n <= nBuffCorr; n++){
    free(cfOrg[n]);
    free(spacetimeCorr[n]);
  }
  free(cfOrg);
  free(spacetimeCorr);
  free(cfVal);
  free(indexCorr);
  free(spacetimeCorrAv);

  free(indexAcf);
  free(viscAcfOrg);
  free(viscAcfAv);
  for(n = 0 ; n <= nBuffAcf ; n ++)
    free(viscAcf[n]);
  free(viscAcf);

}

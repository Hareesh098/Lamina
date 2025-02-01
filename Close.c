#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void Close(){
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

  int n;
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

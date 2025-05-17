#include<stdio.h>
#include"globalExtern.h"
void AccumVacf();
void EvalVacf(){
  int n, nb, ni;
  double viscVec = 0.;
  double v[3];
  for(n = 1 ; n <= nAtom ; n ++){
    v[1] = vx[n] - 0.5*ax[n]*deltaT;
    v[2] = vy[n] - 0.5*ay[n]*deltaT;
    viscVec += v[1]*v[2];
  }
  viscVec += rfAtom;
  for(nb = 1 ; nb <= nBuffAcf ; nb ++){
    indexAcf[nb] ++;
    if(indexAcf[nb] <= 0)continue;
    if(indexAcf[nb] == 1){
      viscAcfOrg[nb] = viscVec;
    }
    ni = indexAcf[nb];
    viscAcf[nb][ni] = viscAcfOrg[nb]*viscVec;
  }
  AccumVacf();
}

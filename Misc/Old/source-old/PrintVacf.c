#include<stdio.h>
#include"globalExtern.h"

void PrintVacf(){
  double tVal;
  int j;
  fprintf(fpvisc,"viscosity acf\n");
  for(j = 1 ; j <= nValAcf ; j ++){
    tVal = (j-1)*stepAcf*deltaT;
    fprintf(fpvisc, "%lf\t %lf\t %lf\n", tVal, viscAcfAv[j], viscAcfAv[j]/viscAcfAv[1]);
  }
  fprintf(fpvisc, "viscosity acf integral : %lf\n", viscAcfInt);
}



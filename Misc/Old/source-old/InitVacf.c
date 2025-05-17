#include<stdio.h>
#include"globalExtern.h"
void ZeroVacf();
void InitVacf(){
  int nb;
  for(nb = 1 ; nb <= nBuffAcf ; nb ++)
    indexAcf[nb] = -(nb-1)*nValAcf/nBuffAcf;
  ZeroVacf();
}

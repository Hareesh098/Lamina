#include<stdio.h>
#include"globalExtern.h"

void ZeroVacf(){
  int j;
  countAcfAv= 0 ;
  for(j = 1 ; j <= nValAcf ; j ++)
    viscAcfAv[j] = 0.;
}

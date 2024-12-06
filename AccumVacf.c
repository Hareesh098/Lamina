#include<stdio.h>
#include"globalExtern.h"
double Integrate(double *, int);
void PrintVacf();
void ZeroVacf();
void AccumVacf(){
  double fac;
  int j, nb;
  for(nb = 1 ; nb <= nBuffAcf ; nb ++){
    if(indexAcf[nb] == nValAcf){
      for(j = 1 ; j <= nValAcf; j ++){
	viscAcfAv[j] +=  viscAcf[nb][j];
      }
      indexAcf[nb] = 0;
      countAcfAv ++;
      if(countAcfAv == limitAcfAv){
	fac = 1./(kinEnergy*region[1]*region[2]*limitAcfAv);
	viscAcfInt = fac*stepAcf*deltaT*Integrate(viscAcfAv, nValAcf);
	PrintVacf();
	ZeroVacf();
      }
    }
  }
}


#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
void AccumProps(int icode){
  if(icode == 0){
    sPotEnergy = ssPotEnergy = 0.;
    sKinEnergy = ssKinEnergy = 0.;
    sPressure = ssPressure = 0.;
    sTotEnergy = ssTotEnergy = 0.; 
    svirSum = 0.;
  }else if(icode == 1){
    sPotEnergy += potEnergy;
    ssPotEnergy += Sqr(potEnergy);
    sKinEnergy += kinEnergy;
    ssKinEnergy += Sqr(kinEnergy);
    sTotEnergy += totEnergy;
    ssTotEnergy += Sqr(totEnergy);
    sPressure += pressure;
    ssPressure += Sqr(pressure);
    svirSum += virSum;
  }else if(icode == 2){
    sPotEnergy /= stepAvg;
    ssPotEnergy /= sqrt(ssPotEnergy/stepAvg - Sqr(sPotEnergy));
    sTotEnergy /= stepAvg;
    ssTotEnergy = sqrt(ssTotEnergy/stepAvg - Sqr(sTotEnergy));
    sKinEnergy /= stepAvg;
    ssKinEnergy = sqrt(ssKinEnergy/stepAvg - Sqr(sKinEnergy));
    sPressure /= stepAvg;
    ssPressure = sqrt(ssPressure/stepAvg - Sqr(sPressure));
    svirSum /= stepAvg;
  }
}

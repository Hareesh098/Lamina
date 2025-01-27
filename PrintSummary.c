#include<stdio.h>
#include"globalExtern.h"

void PrintSummary(){
  fprintf(fpresult, "%0.13lf %0.13lf %0.13lf %0.13lf %0.13lf %0.13lf %0.13lf %0.13lf %0.13lf\n", 
   timeNow, vSum, potEnergy, kinEnergy, totEnergy, uSumPairPerAtom, BondEnergyPerAtom, sPressure, svirSum);
  fflush(fpresult);
}

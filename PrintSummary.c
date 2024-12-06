#include<stdio.h>
#include"globalExtern.h"

void PrintSummary(){
  fprintf(fpresult, "%0.10lf %0.10lf %0.10lf %0.10lf %0.10lf %0.10lf %0.10lf %0.10lf %0.10lf\n", 
   timeNow, vSum, potEnergy, kinEnergy, totEnergy, uSumPairPerAtom, BondEnergyPerAtom, sPressure, svirSum);
  fflush(fpresult);
}

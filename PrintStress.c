#include<stdio.h>
#include"globalExtern.h"

void PrintStress(){
  fprintf(fpstress, "%0.7lf %0.16lf %0.16lf %0.16lf %0.16lf\n", timeNow, virSumxx, virSumyy, virSumxy, pressure);
  fflush(fpstress);
}

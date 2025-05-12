#include<stdio.h>
#include"globalExtern.h"

void PrintStress(){
  fprintf(fpstress, "%0.4lf\t%0.16lf\t%0.16lf\t%0.16lf\t%0.16lf\n", timeNow, virSumxx, virSumyy, virSumxy, pressure);
  fflush(fpstress);
}

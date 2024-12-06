#include<stdio.h>
#include"globalExtern.h"

void PrintMomentum(){
  fprintf(fpmomentum, "%0.10lf %0.10lf %0.10lf\n", timeNow, vSumX, vSumY);
  fflush(fpmomentum);
}

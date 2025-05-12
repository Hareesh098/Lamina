#include<stdio.h>
#include"globalExtern.h"

void PrintMomentum(){
  fprintf(fpmomentum, "%0.4lf\t%0.16lf\t%0.16lf\n", timeNow, vSumX, vSumY);
  fflush(fpmomentum);
}

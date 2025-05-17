#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"
void PrintVrms(){
  fprintf(fpvrms, "%0.4lf\t%0.16lf\n", timeNow, VRootMeanSqr);
  fflush(fpvrms);
  }
  
  
  

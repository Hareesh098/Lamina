#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"
void PrintVrms(){
  int n;
  VSqr = 0.0;
  VMeanSqr = 0.0;
  VRootMeanSqr = 0.0;
  
  if(stepCount == stepTraj){
  fprintf(fpvrms, "#timeNow\tVrms \n");
  }
  
  for(n = 1 ; n <= nAtom ; n ++){
  VSqr += Sqr(vx[n]) + Sqr(vy[n]); 
  }
  VMeanSqr = VSqr/nAtom;
  VRootMeanSqr = sqrt(VMeanSqr);
  
  fprintf(fpvrms, "%0.16lf\t%0.16lf\n", timeNow, VRootMeanSqr);
  fflush(fpvrms);
  
  }
  
  
  

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"
void EvalVrms(){
  int n;
  VSqr = 0.0;
  VMeanSqr = 0.0;
  VRootMeanSqr = 0.0;
    
  for(n = 1 ; n <= nAtom ; n ++){
  VSqr += Sqr(vx[n]) + Sqr(vy[n]); 
  }
  VMeanSqr = VSqr/nAtom;
  VRootMeanSqr = sqrt(VMeanSqr);
  }
  
  
  

#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void ApplyForce(){
 int n;
 double lx;
 lx = regionH[1];  
 fy =  (FyBylx * lx)/nAtomBlock;
 fx =  fxByfy * fy;
 for(n = 1; n <= nAtom; n ++){
 if(molID[n] == 2){
  ax[n] += fx; 
  ay[n] -= fy;
} } }

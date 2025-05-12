#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void DisplaceAtoms(){
 int n;
  for(n = 1; n <= nAtom; n ++){
   if(molID[n] == 2){
    rx[n] += DeltaX; 
    ry[n] += DeltaY;
} } }

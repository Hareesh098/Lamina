#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void DisplaceAtoms(){
 int n;
  for(n = 1; n <= nAtom; n ++){
   if(atomType[n] == 4 || atomType[n] == 5){
    rx[n] += DeltaX; 
    ry[n] += DeltaY;
} } }

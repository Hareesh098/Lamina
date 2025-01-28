#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void DisplaceAtoms(){
 int n;
 double DeltaY;
 DeltaY = 0.0;
 for(n = 1; n <= nAtom; n ++){
 if(atomType[n] == 4 || atomType[n] == 5){
 ry[n] += DeltaY;
} } }

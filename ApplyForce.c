#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void ApplyForce(){
 int n;
 for(n = 1; n <= nAtom; n ++){
 if(atomType[n] == 4 || atomType[n] == 5){
 ay[n] += forceY;
 ax[n] += forceX;
} } }

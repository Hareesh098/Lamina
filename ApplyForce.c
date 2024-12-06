#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void ApplyForce(){
 int n;
 double fx, fy;
 fx = 0.0; fy = 0.0;
 for(n = 1 ; n <= nAtom; n ++){
 ax[n] += fx;
 ay[n] += fy; 
} }

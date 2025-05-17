#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
void ApplyShear(){
 int n;
 for(n = 1 ; n <= nAtom ; n ++){
  rx[n] += strain * ry[n];
  //vx[n] += stranRate * ry[n];
 } }

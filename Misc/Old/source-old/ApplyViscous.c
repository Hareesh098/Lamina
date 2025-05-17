#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void ApplyViscous(){
 int n;
 double gammav;
 gammav = 1.0; 
 for(n = 1 ; n <= nAtom; n ++){
  ax[n] += -gammav * vx[n];
  ay[n] += -gammav * vy[n];
 } }



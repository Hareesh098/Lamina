#include <stdio.h>
#include <math.h>
#include "globalExtern.h"

void ApplyLeesEdwardsBoundaryCond() {
 int n;
 for (n = 1; n <= nAtom; n++) {
//PBC
 if(rx[n] >= regionH[1])
   rx[n] -= region[1];
 else if(rx[n] < -regionH[1])
   rx[n] += region[1];
   
//LEBC
  if(ry[n] >= regionH[2]){
   rx[n] -= shearDisplacement;
   if(rx[n] < -regionH[1]) rx[n] += region[1];
   //vx[n] -= shearVelocity; 
   ry[n] -= region[2];
  }else if(ry[n] < -regionH[2]){
   rx[n] += shearDisplacement;
   if(rx[n] >= regionH[1]) rx[n] -= region[1];
   //vx[n] += shearVelocity; 
   ry[n] += region[2];
  }
 } 
}


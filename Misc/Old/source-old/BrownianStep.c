#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"

void BrownianStep(){
  if(stepCount <= stepEquil){
    double A, S1, S2, T;
    int n;
    S1 = 0.; S2 = 0;
    double halfdt = 0.5*deltaT;
    for (n = 1; n <= nAtom; n++){
      T = vx[n] + halfdt * ax[n];
      S1 += T * ax[n];
      S2 += Sqr(T);
      
      T = vy[n] + halfdt * ay[n];
      S1 += T * ay[n];
      S2 += Sqr(T);
    }
    A = -S1 / S2;
    double C = 1 + A*deltaT ;
    double D = deltaT * (1 + 0.5 * A * deltaT);
    for (n = 1; n <= nAtom; n++){
      vx[n] = C * vx[n] + D * ax[n];
      rx[n] += deltaT * vx[n];
      vy[n] = C * vy[n] + D * ay[n];
      ry[n] += deltaT * vy[n];
    }
  }else{
      int n;
      //SETTING TEMP = 0.0
     if (stepCount == stepEquil+1){
     for(n = 1 ; n <= nAtom ; n ++){
     vx[n] = 0.0;
     vy[n] = 0.0;
     }}
     double zeta = 1.0;
     double dx, dy;
     for(n = 1 ; n <= nAtom ; n ++){
      dx = rx[n]; 
      rx[n] += zeta * ax[n] * deltaT;
      dx = rx[n] - dx; 
      vx[n] = dx/deltaT; 
      dy = ry[n];
      ry[n] += zeta * ay[n] * deltaT;
      dy = ry[n] - dy;
      vy[n] = dy/deltaT;
    }
  }
}
  

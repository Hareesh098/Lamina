#include<stdio.h>
#include"globalExtern.h"
void LeapfrogStep(){
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
     if(atomType[n] == 1 || atomType[n] == 3){
      vx[n] = C * vx[n] + D * ax[n];
      rx[n] += deltaT * vx[n];
      vy[n] = C * vy[n] + D * ay[n];
      ry[n] += deltaT * vy[n];
      }
    }
  }else{
    int n;
    for(n = 1 ; n <= nAtom ; n ++){
      vx[n] += deltaT * ax[n];
      rx[n] += deltaT * vx[n];
      vy[n] += deltaT * ay[n];
      ry[n] += deltaT * vy[n];
} } }
  

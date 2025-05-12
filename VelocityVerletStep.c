#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
void VelocityVerletStep(int icode){
int n;
 if(icode == 1){
 for (n= 1; n <= nAtom; n++) {
  if(atomType[n] != freezeAtomType){
  vx[n] += ax[n] * 0.5 * deltaT; 
  vy[n] += ay[n] * 0.5 * deltaT;
  rx[n] += vx[n] * deltaT; 
  ry[n] += vy[n] * deltaT;
  } } }
  else if(icode == 2){
  for(n = 1; n <= nAtom; n++) {
  if(atomType[n] != freezeAtomType){
   vx[n] += ax[n] * 0.5 * deltaT; 
   vy[n] += ay[n] * 0.5 * deltaT;
} } } }


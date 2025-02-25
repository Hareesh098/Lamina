#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"
void EvalCom(){
 int n;
 ComX = 0.0; ComY = 0.0; ComXRatio = 0.0; ComYRatio = 0.0;
 TotalMass = 0.0;
  
 for(n=1; n<=nAtom; n++){
 if(atomType[n] == 4 || atomType[n] == 5){
  ComX += atomMass[n] * rxUnwrap[n]; 
  ComY += atomMass[n] * ryUnwrap[n]; 
  TotalMass += atomMass[n];
  } }

  ComX = ComX/TotalMass;
  ComY = ComY/TotalMass;

  if(timeNow == 0.0){
  ComX0 = ComX; ComY0 = ComY;
  }
  ComXRatio = ComX/ComX0;   ComYRatio = ComY/ComY0;
 }
  
  
  

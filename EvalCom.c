#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"
void EvalCom(){
 int n;
 ComX = 0.0; ComY = 0.0;
 TotalMass = 0.0;
  
 for(n = 1 ; n <= nAtom ; n ++){
 if(atomType[n] == 4 || atomType[n] == 5){
  ComX += atomMass[n] * rx[n]; 
  ComY += atomMass[n] * ry[n]; 
  TotalMass += atomMass[n];
  } }

  ComX = ComX/TotalMass;
  ComY = ComY/TotalMass;
 }
  
  
  

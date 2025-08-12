/*
 * This file is part of Lamina.
 *
 * Lamina is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lamina is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lamina. If not, see <https://www.gnu.org/licenses/>.

 Copyright (C) 2025 Harish Charan, University of Durham, UK

 */


#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "../source/global.h"

void Init(){
 nAtom = 4;
 nBond = 1;
 gamman = 1.0;
 DampFlag = 1;
 Kn = 1.0;
 region[1] = region[2] =   20.0;
 regionH[1] = regionH[2] = 10.0;
 shearDisplacement = 0.0;


  rx = (double*)malloc((nAtom + 1) * sizeof(double));
  ry = (double*)malloc((nAtom + 1) * sizeof(double));
  vx = (double*)malloc((nAtom + 1) * sizeof(double));
  vy = (double*)malloc((nAtom + 1) * sizeof(double));
  fx = (double*)malloc((nAtom + 1) * sizeof(double));
  fy = (double*)malloc((nAtom + 1) * sizeof(double));
  ax = (double*)malloc((nAtom + 1) * sizeof(double));
  ay = (double*)malloc((nAtom + 1) * sizeof(double));
  fax = (double*)malloc((nAtom + 1) * sizeof(double));
  fay = (double*)malloc((nAtom + 1) * sizeof(double));
  atomID = (int*)malloc((nAtom+1) * sizeof(int));
  atomType = (int*)malloc((nAtom+1) * sizeof(int));
  atomRadius = (double*)malloc((nAtom + 1) * sizeof(double));
  atomMass = (double*)malloc((nAtom + 1) * sizeof(double));
  speed = (double*)malloc((nAtom + 1) * sizeof(double));
  atom1 = (int*)malloc((nBond+1)*sizeof(int));
  atom2 = (int*)malloc((nBond+1)*sizeof(int)); 
  BondID = (int*)malloc((nBond+1)*sizeof(int));
  BondType = (int*)malloc((nBond+1)*sizeof(int));
  kb = (double*)malloc((nBond+1)*sizeof(double));
  ro = (double*)malloc((nBond+1)*sizeof(double));
  BondEnergy = (double*)malloc((nBond+1)*sizeof(double));
  BondLength =(double*)malloc((nBond+1)*sizeof(double));
  discDragx = (double*)malloc((nAtom + 1) * sizeof(double)); 
  discDragy = (double*)malloc((nAtom + 1) * sizeof(double)); 
  nodeDragx = (double*)malloc((nAtom + 1) * sizeof(double));
  nodeDragy = (double*)malloc((nAtom + 1) * sizeof(double));
  ImageX = (int*)malloc((nAtom+1) * sizeof(int));
  ImageY = (int*)malloc((nAtom+1) * sizeof(int));
  rxUnwrap = (double*)malloc((nAtom + 1) * sizeof(double));
  ryUnwrap = (double*)malloc((nAtom + 1) * sizeof(double));
  molID = (int*)malloc((nAtom+1) * sizeof(int));


 rx[1] = 0.0; ry[1] = 0.0;
 rx[2] = 2.0; ry[2] = 0.0;
 rx[3] = 4.0; ry[3] = -1.0;
 rx[4] = 4.0; ry[4] = 0.9;

 vx[1] = 0.0; vy[1] = 0.0;
 vx[2] = 0.0; vy[2] = 0.0;
 vx[3] = 0.0; vy[3] = 0.0;
 vx[4] = 0.0; vy[4] = 0.0;

 molID[1] = 1;   
 molID[2] = 1; 
 molID[3] = 2;   
 molID[4] = 2; 

 atomType[1] = 1;   
 atomType[2] = 1; 
 atomType[3] = 2;   
 atomType[4] = 2; 

 atomRadius[1] = 0.0;   
 atomRadius[2] = 0.0; 
 atomRadius[3] = 1.0;   
 atomRadius[4] = 1.0; 

 for(int n = 1; n <= nAtom; n ++){
 atomMass[n] = 1.0;
 atomID[n] = n;
 }
 
 BondID[1] = 1;
 BondType[1] = 1;
 atom1[1] = 1;
 atom2[1] = 2;
 kb[1] = 1.0;
 ro[1] = 1.1;
 int n;
 
  //2D-List of bonded atoms. This is used to remove pair interaction
 //calculation for the bonded atoms
   isBonded = (int**)malloc((nAtom + 1) * sizeof(int*));
  for (int i = 0; i <= nAtom; i++) {
    isBonded[i] = (int*)malloc((nAtom + 1) * sizeof(int));
    for (int j = 0; j <= nAtom; j++) {
        isBonded[i][j] = 0;
    }
  }
  
  for (n = 1; n <= nBond; n++) {
    int i = atom1[n];
    int j = atom2[n];
    isBonded[i][j] = 1;
    isBonded[j][i] = 1; // symmetric
}

 // List the interface atoms
 nAtomInterface = 0;
 nAtomBlock = 0;
 nDiscInterface = 0;
 bigDiameter = 2.8;
 InterfaceWidth = 5.0 * bigDiameter;

 for(n = 1; n <= nAtom; n++){
  if(fabs(ry[n]) < InterfaceWidth){
  nAtomInterface++;
  }
  if(molID[n] == 2){
  nAtomBlock++;
  } 
  if(atomRadius[n] != 0.0){
  nDiscInterface++;
  } } 

  
  int BondPairInteract;
  BondPairInteract = 0;
  int m;
  if(BondPairInteract == 1){
   atomIDInterface =  (int *)malloc((nAtomInterface+1)*sizeof(int));
   m = 1;
   for(n=1; n<=nAtom; n++){
    if(fabs(ry[n]) < InterfaceWidth){
    atomIDInterface[m] = atomID[n]; 
    m++; 
  } } }
  else if(BondPairInteract == 0){
   nAtomInterface = nDiscInterface;
   atomIDInterface =  (int *)malloc((nAtomInterface+1)*sizeof(int));
   m = 1;
   for(n=1; n<=nAtom; n++){
    if(atomRadius[n] != 0.0){
    atomIDInterface[m] = atomID[n]; 
    m++; 
  } } }

  nPairTotal = 0.5 * nAtomInterface * (nAtomInterface-1);
  PairID = (int*)malloc((nPairTotal+1) * sizeof(int));
  Pairatom1 = (int*)malloc((nPairTotal+1) * sizeof(int));
  Pairatom2 = (int*)malloc((nPairTotal+1) * sizeof(int));
  PairXij = (double*)malloc((nPairTotal+1) * sizeof(double));
  PairYij = (double*)malloc((nPairTotal+1) * sizeof(double));
   


}

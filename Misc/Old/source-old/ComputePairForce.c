#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
#include "ComputePairForce.h"


void ComputePairForce(int normFlag){
double dr[NDIM+1], fcVal, rr, ri, r, uVal;
int n, i,j;
uVal = 0.0;  uSumPair = 0.0 ; 
virSumPair = 0.0; virSumPairxx = 0.0; virSumPairyy = 0.0; virSumPairxy = 0.0;

for(n = 1 ; n <= nAtom ; n ++){
 ax[n] = 0.0;
 ay[n] = 0.0;
 discDragx[n] = 0.0;
 discDragy[n] = 0.0;
}
for(n = 1; n <= nPairTotal; n ++){
 PairID[n] = 0;
 Pairatom1[n] = 0;
 Pairatom2[n] = 0;
 PairXij[n] = 0.0; 
 PairYij[n] = 0.0; 
}


Kn = 1.0;
double vr[NDIM+1], fdVal, rri;
nPairActive = 0;
double meff;
meff = 0.0;
int atomIDi, atomIDj;
//int processThisPair = 1;

for(i=1;i<=nAtomInterface;i++){
 for(j=i+1;j<=nAtomInterface;j++){
  atomIDi = atomIDInterface[i];
  atomIDj = atomIDInterface[j];
  if (isBonded[atomIDi][atomIDj] == 0) { //To exclude pair interaction between bonded atoms 
  rr = 0.0; rri = 0.0; fcVal = 0.0;  fdVal = 0.0; strech = 0.0;
  RadiusIJ = 0.0;
  
  dr[1] = rx[atomIDi] - rx[atomIDj];
  if(dr[1] >= regionH[1]) 
   dr[1] -= region[1];
  else if(dr[1] < -regionH[1]) 
    dr[1] += region[1];

  dr[2] = ry[atomIDi] - ry[atomIDj];
   if(dr[2] >= regionH[2]){
    dr[1] -= shearDisplacement;
    if(dr[1] < -regionH[1]) dr[1] += region[1];
    dr[2] -= region[2];
  }else if(dr[2] < -regionH[2]){
   dr[1] += shearDisplacement;
    if(dr[1] >= regionH[1]) dr[1] -= region[1];
   dr[2] += region[2];
  }

  rr = Sqr(dr[1]) + Sqr(dr[2]);
  RadiusIJ = atomRadius[atomIDi] + atomRadius[atomIDj];
  SqrRadiusIJ = Sqr(RadiusIJ);
  if(rr < SqrRadiusIJ){
   r = sqrt(rr);
   ri = 1.0/r;
   rri = 1.0/rr;
   RadiusIJInv = 1.0/RadiusIJ;
   strech = (RadiusIJ - r);
   uVal = 0.5 * Kn * Sqr(strech);
   
   //NormFlag
   if(normFlag == 1){ 
    strech = strech * RadiusIJInv;
    uVal = 0.5 * Kn * RadiusIJ * Sqr(strech);
    }
   
   fcVal = Kn * strech * ri;
   vr[1] = vx[atomIDi] - vx[atomIDj];
   vr[2] = vy[atomIDi] - vy[atomIDj];

   nPairActive++;
   PairID[nPairActive] = nPairActive;
   Pairatom1[nPairActive] = atomIDi;
   Pairatom2[nPairActive] = atomIDj;
   PairXij[nPairActive] = dr[1]; 
   PairYij[nPairActive] = dr[2]; 
   
   //DampFlag = 1
   if(DampFlag == 1){
   meff = (atomMass[atomIDi]*atomMass[atomIDj])/(atomMass[atomIDi] + atomMass[atomIDj]);
   fdVal = -gamman * meff * (vr[1]*dr[1] + vr[2]*dr[2]) * rri; //disc-disc drag

   discDragx[atomIDi] =  fdVal * dr[1]; //disc-disc drag
   discDragy[atomIDi] =  fdVal * dr[2]; //disc-disc drag
   discDragx[atomIDj] = -fdVal * dr[1]; //disc-disc drag
   discDragy[atomIDj] = -fdVal * dr[2]; //disc-disc drag

   discDragx[nPairActive] = discDragx[atomIDi];
   discDragy[nPairActive] = discDragy[atomIDi];
   
 
   ax[atomIDi] += (fcVal + fdVal) * dr[1];
   ay[atomIDi] += (fcVal + fdVal) * dr[2];
   ax[atomIDj] += -(fcVal + fdVal) * dr[1];
   ay[atomIDj] += -(fcVal + fdVal) * dr[2];
  }

  //DampFlag = 2
  else if(DampFlag == 2){
   discDragx[atomIDi] =  -gamman * vr[1]; //disc-disc drag
   discDragy[atomIDi] =  -gamman * vr[2]; //disc-disc drag
   discDragx[atomIDj] = -(-gamman * vr[1]); //disc-disc drag
   discDragy[atomIDj] = -(-gamman * vr[2]); //disc-disc drag

   discDragx[nPairActive] = discDragx[atomIDi];
   discDragy[nPairActive] = discDragy[atomIDi];
   

   ax[atomIDi] +=  (fcVal * dr[1] - gamman * vr[1]);
   ay[atomIDi] +=  (fcVal * dr[2] - gamman * vr[2]);
   ax[atomIDj] += -(fcVal * dr[1] - gamman * vr[1]);
   ay[atomIDj] += -(fcVal * dr[2] - gamman * vr[2]);
  }
  
  //DampFlag = 3. Suzanne PRL, 130, 178203 (2023) version 
  else if(DampFlag == 3){
  //Track compression velocity
  DeltaXijNew = dr[1];
  DeltaYijNew = dr[2];
  if(stepCount == 0) { // Initialization step
   DeltaXijOldPair[atomIDi][atomIDj] = DeltaXijNew;
   DeltaYijOldPair[atomIDi][atomIDj] = DeltaYijNew;
   }

   DeltaXij = DeltaXijNew - DeltaXijOldPair[atomIDi][atomIDj];
   DeltaYij = DeltaYijNew - DeltaYijOldPair[atomIDi][atomIDj];
   DeltaVXij = DeltaXij / deltaT;
   DeltaVYij = DeltaYij / deltaT;
   
   // Update history for next step
   DeltaXijOldPair[atomIDi][atomIDj] = DeltaXijNew;
   DeltaYijOldPair[atomIDi][atomIDj] = DeltaYijNew;
     
   discDragx[atomIDi] =  -gamman * DeltaVXij; //disc-disc drag
   discDragy[atomIDi] =  -gamman * DeltaVYij; //disc-disc drag
   discDragx[atomIDj] = -(-gamman * DeltaVXij); //disc-disc drag
   discDragy[atomIDj] = -(-gamman * DeltaVYij); //disc-disc drag
   
   discDragx[nPairActive] = discDragx[atomIDi];
   discDragy[nPairActive] = discDragy[atomIDi];

   ax[atomIDi] +=  (fcVal * dr[1] - gamman * DeltaVXij);
   ay[atomIDi] +=  (fcVal * dr[2] - gamman * DeltaVYij);
   ax[atomIDj] += -(fcVal * dr[1] - gamman * DeltaVXij);
   ay[atomIDj] += -(fcVal * dr[2] - gamman * DeltaVYij);
  }

  //In the following, for stress/virial term (fcVal + fdVal) is used since the total pair force = Hookean Interaction + relative velocity drag
  uSumPair +=  0.5 * uVal;
  virSumPair += 0.5 * (fcVal + fdVal) * rr; 
  virSumPairxx += 0.5 * (fcVal + fdVal) * dr[1] * dr[1];
  virSumPairyy += 0.5 * (fcVal + fdVal) * dr[2] * dr[2];
  virSumPairxy += 0.5 * (fcVal + fdVal) * dr[1] * dr[2];
    }
  else { //Resetting the distance between two discs when they are not in contact 
   DeltaXijOldPair[atomIDi][atomIDj] = 0.0;
   DeltaYijOldPair[atomIDi][atomIDj] = 0.0;
   DeltaXijOldPair[atomIDj][atomIDi] = 0.0;
   DeltaYijOldPair[atomIDj][atomIDi] = 0.0;
    } 
   }
  }
 }
}




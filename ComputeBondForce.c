#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"globalExtern.h"

void ComputeBondForce(){
  int n;
  double dr[NDIM+1], r, rr, ri, roi;
  double uVal, fcVal;

  uVal = 0.0; TotalBondEnergy = 0.0;
  virSumBond = 0.0; virSumBondxx = 0.0; virSumBondyy = 0.0; virSumBondxy = 0.0;

  double vr[NDIM+1], fdVal, rri;
 
  for(n = 1 ; n <= nAtom ; n ++){
   nodeDragx[n] = 0.0;
   nodeDragy[n] = 0.0;
  } //Important change made on 03Apr2025. Mention it in GitHub

  int atom1ID, atom2ID;
   
  for(n=1; n<=nBond; n++){
   rr = 0.0; rri = 0.0; fcVal = 0.0;  fdVal = 0.0; strech = 0.0;
   atom1ID = atom1[n];
   atom2ID = atom2[n];
   
   dr[1] = rx[atom1ID] - rx[atom2ID];
   if(dr[1] >= regionH[1]) 
    dr[1] -= region[1];
   else if(dr[1] < -regionH[1]) 
    dr[1] += region[1];

   dr[2] = ry[atom1ID] - ry[atom2ID];
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
   r = sqrt(rr);
   rri = 1.0/rr;
   ri = 1.0/r;
   roi = 1.0/ro[n];
   strech = (r * roi - 1.0);
   uVal = 0.5 * kb[n] * ro[n] * Sqr(strech);
   fcVal = -kb[n] * strech * ri; //F = -Grad U
   
   vr[1] = vx[atom1ID] - vx[atom2ID];
   vr[2] = vy[atom1ID] - vy[atom2ID];
   fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rri; //node-node drag
   
   //DampFlag = 1. LAMMPS version
   if(DampFlag == 1){
   nodeDragx[atom1ID] =  fdVal * dr[1];  //node-node drag  //Important change made on 03Apr2025. Mention it in GitHub
   nodeDragy[atom1ID] =  fdVal * dr[2];  //node-node drag  //Adding the drag forces is wrong. Only add the 
   nodeDragx[atom2ID] =  -fdVal * dr[1];  //node-node drag //total force 
   nodeDragy[atom2ID] =  -fdVal * dr[2];  //node-node drag
      
   ax[atom1ID] +=  (fcVal + fdVal) * dr[1];
   ay[atom1ID] +=  (fcVal + fdVal) * dr[2];
   ax[atom2ID] += -(fcVal + fdVal) * dr[1];
   ay[atom2ID] += -(fcVal + fdVal) * dr[2];
   }
   
   //DampFlag = 2. Suzanne notes version
   else if(DampFlag == 2){
   nodeDragx[atom1ID] =  -gamman * vr[1];  //node-node drag
   nodeDragy[atom1ID] =  -gamman * vr[2]; //node-node drag
   nodeDragx[atom2ID] =  -(-gamman * vr[1]);  //node-node drag
   nodeDragy[atom2ID] =  -(-gamman * vr[2]);  //node-node drag
      
   ax[atom1ID] +=  (fcVal * dr[1] - gamman * vr[1]);
   ay[atom1ID] +=  (fcVal * dr[2] - gamman * vr[2]);
   ax[atom2ID] += -(fcVal * dr[1] - gamman * vr[1]);
   ay[atom2ID] += -(fcVal * dr[2] - gamman * vr[2]);
   }

   //DampFlag = 3. Suzanne PRL, 130, 178203 (2023) version
   else if(DampFlag == 3){
    DeltaXijNew = dr[1];
    DeltaYijNew = dr[2];

    if(stepCount == 0) {  // First timestep
     DeltaXijOld[n] = DeltaXijNew;
     DeltaYijOld[n] = DeltaYijNew;
    }

    DeltaXij = DeltaXijNew - DeltaXijOld[n];
    DeltaYij = DeltaYijNew - DeltaYijOld[n];
    DeltaVXij = DeltaXij / deltaT;
    DeltaVYij = DeltaYij / deltaT;
   
    // Now update for the next timestep
    DeltaXijOld[n] = DeltaXijNew;
    DeltaYijOld[n] = DeltaYijNew;

    nodeDragx[atom1ID] =  -gamman * DeltaVXij;  //node-node drag
    nodeDragy[atom1ID] =  -gamman * DeltaVYij; //node-node drag
    nodeDragx[atom2ID] =  -(-gamman * DeltaVXij);  //node-node drag
    nodeDragy[atom2ID] =  -(-gamman * DeltaVYij);  //node-node drag
      
    ax[atom1ID] +=  (fcVal * dr[1] - gamman * DeltaVXij);
    ay[atom1ID] +=  (fcVal * dr[2] - gamman * DeltaVYij);
    ax[atom2ID] += -(fcVal * dr[1] - gamman * DeltaVXij);
    ay[atom2ID] += -(fcVal * dr[2] - gamman * DeltaVYij);
   }


   BondLength[n] = r;
   BondEnergy[n] = uVal; //No 0.5 factor since it is the energy of the bond
   TotalBondEnergy   +=  BondEnergy[n]; 

   virSumBond +=   0.5 * (fcVal + fdVal) * rr;
   virSumBondxx += 0.5 * (fcVal + fdVal) * dr[1] * dr[1];
   virSumBondyy += 0.5 * (fcVal + fdVal) * dr[2] * dr[2];
   virSumBondxy += 0.5 * (fcVal + fdVal) * dr[1] * dr[2];
} }

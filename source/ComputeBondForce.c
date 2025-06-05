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

#include "ComputeBondForce.h"

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<omp.h>
#include"global.h"

void ComputeBondForce(){
  int n;
  TotalBondEnergy = 0.0;
  virSumBond = 0.0; virSumBondxx = 0.0; virSumBondyy = 0.0; virSumBondxy = 0.0;


  #pragma omp parallel for
  for(n = 1 ; n <= nAtom ; n ++){
   nodeDragx[n] = 0.0;
   nodeDragy[n] = 0.0;
  } //Important change made on 03Apr2025. Mention it in GitHub


  #pragma omp parallel for reduction(+:TotalBondEnergy,virSumBond,virSumBondxx,virSumBondyy,virSumBondxy)
  for(n=1; n<=nBond; n++){
   int atom1ID, atom2ID;
   double dr[NDIM+1], r, rr, ri, roi;
   double uVal, fcVal;
   double vr[NDIM+1], fdVal, rri;
   double strech_local;
   rr = 0.0; rri = 0.0; fcVal = 0.0;  fdVal = 0.0; strech_local = 0.0;
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
   strech_local = (r * roi - 1.0);
   uVal = 0.5 * kb[n] * ro[n] * Sqr(strech_local);
   fcVal = -kb[n] * strech_local * ri; //F = -Grad U
   
   vr[1] = vx[atom1ID] - vx[atom2ID];
   vr[2] = vy[atom1ID] - vy[atom2ID];
   fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rri; //node-node drag
   
   //DampFlag = 1. LAMMPS version
   if(DampFlag == 1){
   #pragma omp atomic write
   nodeDragx[atom1ID] =  fdVal * dr[1];  //node-node drag  //Important change made on 03Apr2025. Mention it in GitHub
   #pragma omp atomic write
   nodeDragy[atom1ID] =  fdVal * dr[2];  //node-node drag  //Adding the drag forces is wrong. Only add the
   #pragma omp atomic write
   nodeDragx[atom2ID] =  -fdVal * dr[1];  //node-node drag //total force
   #pragma omp atomic write
   nodeDragy[atom2ID] =  -fdVal * dr[2];  //node-node drag

   #pragma omp atomic
   ax[atom1ID] +=  (fcVal + fdVal) * dr[1];
   #pragma omp atomic
   ay[atom1ID] +=  (fcVal + fdVal) * dr[2];
   #pragma omp atomic
   ax[atom2ID] += -(fcVal + fdVal) * dr[1];
   #pragma omp atomic
   ay[atom2ID] += -(fcVal + fdVal) * dr[2];
   }
   
   //DampFlag = 2. Suzanne notes version
   else if(DampFlag == 2){
   #pragma omp atomic write
   nodeDragx[atom1ID] =  -gamman * vr[1];  //node-node drag
   #pragma omp atomic write
   nodeDragy[atom1ID] =  -gamman * vr[2]; //node-node drag
   #pragma omp atomic write
   nodeDragx[atom2ID] =  -(-gamman * vr[1]);  //node-node drag
   #pragma omp atomic write
   nodeDragy[atom2ID] =  -(-gamman * vr[2]);  //node-node drag

   #pragma omp atomic
   ax[atom1ID] +=  (fcVal * dr[1] - gamman * vr[1]);
   #pragma omp atomic
   ay[atom1ID] +=  (fcVal * dr[2] - gamman * vr[2]);
   #pragma omp atomic
   ax[atom2ID] += -(fcVal * dr[1] - gamman * vr[1]);
   #pragma omp atomic
   ay[atom2ID] += -(fcVal * dr[2] - gamman * vr[2]);
   }

   //DampFlag = 3. Suzanne PRL, 130, 178203 (2023) version
   else if(DampFlag == 3){
    double DeltaXijNew_local = dr[1];
    double DeltaYijNew_local = dr[2];

    if(stepCount == 0) {  // First timestep
     DeltaXijOld[n] = DeltaXijNew_local;
     DeltaYijOld[n] = DeltaYijNew_local;
   }

    double DeltaXij_local = DeltaXijNew_local - DeltaXijOld[n];
    double DeltaYij_local = DeltaYijNew_local - DeltaYijOld[n];
    double DeltaVXij_local = DeltaXij_local / deltaT;
    double DeltaVYij_local = DeltaYij_local / deltaT;
   
    // Now update for the next timestep
    DeltaXijOld[n] = DeltaXijNew_local;
    DeltaYijOld[n] = DeltaYijNew_local;

    #pragma omp atomic write
    nodeDragx[atom1ID] =  -gamman * DeltaVXij_local;  //node-node drag
    #pragma omp atomic write
    nodeDragy[atom1ID] =  -gamman * DeltaVYij_local; //node-node drag
    #pragma omp atomic write
    nodeDragx[atom2ID] =  -(-gamman * DeltaVXij_local);  //node-node drag
    #pragma omp atomic write
    nodeDragy[atom2ID] =  -(-gamman * DeltaVYij_local);  //node-node drag

    #pragma omp atomic
    ax[atom1ID] +=  (fcVal * dr[1] - gamman * DeltaVXij_local);
    #pragma omp atomic
    ay[atom1ID] +=  (fcVal * dr[2] - gamman * DeltaVYij_local);
    #pragma omp atomic
    ax[atom2ID] += -(fcVal * dr[1] - gamman * DeltaVXij_local);
    #pragma omp atomic
    ay[atom2ID] += -(fcVal * dr[2] - gamman * DeltaVYij_local);
   }


   BondLength[n] = r;
   BondEnergy[n] = uVal; //No 0.5 factor since it is the energy of the bond
   TotalBondEnergy   +=  BondEnergy[n]; 

   virSumBond +=   0.5 * (fcVal + fdVal) * rr;
   virSumBondxx += 0.5 * (fcVal + fdVal) * dr[1] * dr[1];
   virSumBondyy += 0.5 * (fcVal + fdVal) * dr[2] * dr[2];
   virSumBondxy += 0.5 * (fcVal + fdVal) * dr[1] * dr[2];
} }

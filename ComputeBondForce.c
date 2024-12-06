#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"globalExtern.h"

void ComputeBondForce(){
  int n;
  double strech;
  double dr[NDIM+1], r, rr, ri, roi;
  double uVal,fcVal;
  uVal = 0.0; fcVal = 0.0; TotalBondEnergy = 0.0;
  virSumBond = 0.0; virSumBondxx = 0.; virSumBondyy = 0.; virSumBondxy = 0.;

  for(n=1; n<=nBond; n++){

   dr[1] = rx[atom1[n]] - rx[atom2[n]];
   if(dr[1] >= regionH[1]) 
    dr[1] -= region[1];
   else if(dr[1] < -regionH[1]) 
    dr[1] += region[1];

   dr[2] = ry[atom1[n]] - ry[atom2[n]];
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
   ri = 1.0/r;
   strech = ((r - ro[BondType[n]])/ro[BondType[n]]);
   uVal = 0.5*kb[BondType[n]]*Sqr(strech);
   roi = 1.0/ro[BondType[n]];
   fcVal = -kb[BondType[n]] * strech * roi * ri; //F = -Grad U
   ax[atom1[n]] +=  fcVal * dr[1];
   ay[atom1[n]] +=  fcVal * dr[2];
   ax[atom2[n]] += -fcVal * dr[1];
   ay[atom2[n]] += -fcVal * dr[2];
   BondLength[n] = r;
   BondEnergy[n] = uVal; 
   TotalBondEnergy   +=  BondEnergy[n]; 

   virSumBond += 0.5 * fcVal * rr;
   virSumBondxx += 0.5 * fcVal * dr[1] * dr[1];
   virSumBondyy += 0.5 * fcVal * dr[2] * dr[2];
   virSumBondxy += 0.5 * fcVal * dr[1] * dr[2];
} }

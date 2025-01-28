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
  gamman = 1.0;
  double vr[NDIM+1], fdVal, rrinv;
  //double f, fd;
  //fd = 0.0;
  rrinv = 0.0;  fdVal = 0.0; 

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
   strech = ((r - ro[BondID[n]])/ro[BondID[n]]);
   uVal = 0.5*kb[BondID[n]]*Sqr(strech);
   roi = 1.0/ro[BondID[n]];
   rrinv = 1.0/rr;
   vr[1] = vx[atom1[n]] - vx[atom2[n]];
   vr[2] = vy[atom1[n]] - vy[atom2[n]];
   fcVal = -kb[BondID[n]] * strech * roi * ri; //F = -Grad U
   fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rrinv; //node-node drag

   nodeDragx[atom1[n]] +=  fdVal * dr[1];  //node-node drag
   nodeDragy[atom1[n]] +=  fdVal * dr[2];  //node-node drag
   nodeDragx[atom2[n]] +=  -fdVal * dr[1];  //node-node drag
   nodeDragy[atom2[n]] +=  -fdVal * dr[2];  //node-node drag
      
   ax[atom1[n]] +=  (fcVal + fdVal) * dr[1];
   ay[atom1[n]] +=  (fcVal + fdVal) * dr[2];
   ax[atom2[n]] += -(fcVal + fdVal) * dr[1];
   ay[atom2[n]] += -(fcVal + fdVal) * dr[2];
   
   BondLength[n] = r;
   BondEnergy[n] = uVal; //No 0.5 factor since it is the energy of the bond
   TotalBondEnergy   +=  BondEnergy[n]; 

   virSumBond +=   0.5 * (fcVal + fdVal) * rr;
   virSumBondxx += 0.5 * (fcVal + fdVal) * dr[1] * dr[1];
   virSumBondyy += 0.5 * (fcVal + fdVal) * dr[2] * dr[2];
   virSumBondxy += 0.5 * (fcVal + fdVal) * dr[1] * dr[2];
} }

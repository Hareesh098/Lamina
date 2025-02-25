#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
void ComputePairForce(){
double dr[NDIM+1], fcVal, rr, ri, r, uVal;
int n, i,j;
uVal = 0.0;  uSumPair = 0.0 ; fcVal = 0.0;
virSumPair = 0.0; virSumPairxx = 0.; virSumPairyy = 0.; virSumPairxy = 0.;

for(n = 1 ; n <= nAtom ; n ++){
 ax[n] = 0.;
 ay[n] = 0.;
 discDragx[n] = 0.0;
 discDragy[n] = 0.0;
}

RadiusIJ = 0.0;
gamman = 1.0;
Kn = 1.0;
double vr[NDIM+1], fdVal, rrinv;
rrinv = 0.0; fdVal = 0.0; 

for(i=1;i<=nAtomInterface;i++){
 for(j=i+1;j<=nAtomInterface;j++){

 if(atomRadius[atomIDInterface[i]] > 0.0 &&  atomRadius[atomIDInterface[j]] > 0.0){
  dr[1] = rx[atomIDInterface[i]] - rx[atomIDInterface[j]];
   if(dr[1] >= regionH[1]) 
    dr[1] -= region[1];
   else if(dr[1] < -regionH[1]) 
    dr[1] += region[1];

  dr[2] = ry[atomIDInterface[i]] - ry[atomIDInterface[j]];
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
  RadiusIJ = atomRadius[atomIDInterface[i]] + atomRadius[atomIDInterface[j]];
  SqrRadiusIJ = Sqr(RadiusIJ);
  if(rr < SqrRadiusIJ){
   r = sqrt(rr);
   ri = 1.0/r;
   rrinv = 1.0/rr;
   vr[1] = vx[atomIDInterface[i]] - vx[atomIDInterface[j]];
   vr[2] = vy[atomIDInterface[i]] - vy[atomIDInterface[j]];
   RadiusIJInv = 1.0/RadiusIJ;
   uVal = 0.5*Kn*RadiusIJ*Sqr(1.0 - r * RadiusIJInv);
   fcVal = Kn * (1.0 - r * RadiusIJInv) * ri;
   fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rrinv; //disc-disc drag

   discDragx[atomIDInterface[i]] +=  fdVal * dr[1]; //disc-disc drag
   discDragy[atomIDInterface[i]] +=  fdVal * dr[2]; //disc-disc drag
   discDragx[atomIDInterface[j]] += -fdVal * dr[1]; //disc-disc drag
   discDragy[atomIDInterface[j]] += -fdVal * dr[2]; //disc-disc drag

   ax[atomIDInterface[i]] += (fcVal + fdVal) * dr[1];
   ay[atomIDInterface[i]] += (fcVal + fdVal) * dr[2];
   ax[atomIDInterface[j]] += -(fcVal + fdVal) * dr[1];
   ay[atomIDInterface[j]] += -(fcVal + fdVal) * dr[2];


  //In the following, for stress/virial term (fcVal + fdVal) is used since the total pair force = Hookean Interaction + relative velocity drag
  uSumPair +=  0.5 * uVal;
  virSumPair += 0.5 * (fcVal + fdVal) * rr; 
  virSumPairxx += 0.5 * (fcVal + fdVal) * dr[1] * dr[1];
  virSumPairyy += 0.5 * (fcVal + fdVal) * dr[2] * dr[2];
  virSumPairxy += 0.5 * (fcVal + fdVal) * dr[1] * dr[2];
  } 

} 

} }

}




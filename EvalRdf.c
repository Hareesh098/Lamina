#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
void EvalRdf(){    
  real dr[NDIM+1], deltaR, normFac, rr, rrRange;
  int j1, j2, n;
  countRdf ++;
  if(countRdf == 1){
    for(n = 1 ; n <= sizeHistRdf ; n ++)
      histRdf[n] = 0.;
  }
  rrRange = Sqr(rangeRdf);
  deltaR = rangeRdf / sizeHistRdf;
  for(j1 = 1 ; j1 <= nAtom - 1 ; j1 ++){
    for(j2 = j1 + 1 ; j2 <= nAtom ; j2 ++){

      dr[1] = rx[j1] - rx[j2];
      if(fabs(dr[1]) > regionH[1])
	dr[1] -= SignR(region[1], dr[1]);

      dr[2] = ry[j1] - ry[j2];
      if(fabs(dr[2]) > regionH[2])
	dr[2] -= SignR(region[2], dr[2]);

      rr = Sqr(dr[1]) + Sqr(dr[2]);

      if(rr < rrRange){
	n = (int)(sqrt(rr)/deltaR) + 1;
	histRdf[n] ++;
      }
    }
  }

  if(countRdf == limitRdf){
    normFac = region[1]*region[2] / (M_PI*Sqr(deltaR)*nAtom*nAtom*countRdf );
    for(n = 1 ; n <= sizeHistRdf ; n ++)
      histRdf[n] *= normFac/(n-0.5);
    // PRINT THE RADIAL DISTRIBUTION DATA ON TO DISK FILE
    real rBin;
    int n;
    fprintf(fprdf,"rdf @ timeNow %lf\n", timeNow);
    for(n = 1 ; n <= sizeHistRdf ; n ++){
      rBin = (n - 0.5)*rangeRdf/sizeHistRdf;
      fprintf(fprdf, "%lf %lf\n", rBin, histRdf[n]);
    }
  }

}


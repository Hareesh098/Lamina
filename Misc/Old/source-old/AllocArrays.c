#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void AllocArrays(){
  int n;
  // SPACETIME CORRELATIONS
  cfOrg = (double **) malloc ((nBuffCorr+1)*sizeof(double *));
  for (n = 0; n <= nBuffCorr; n++)
    cfOrg[n] = (double *) malloc ((2*nFunCorr+1)*sizeof(double));
  cfVal = (double *) malloc ((2*nFunCorr+1)*sizeof(double));
  indexCorr = (int *) malloc ((nBuffCorr+1)*sizeof(int));
  spacetimeCorr = (double **) malloc ((nBuffCorr+1)*sizeof(double));
  for (n = 0; n <= nBuffCorr; n++)
    spacetimeCorr[n] = (double *) malloc ((nFunCorr*nValCorr+1)*sizeof(double));
  spacetimeCorrAv = (double *) malloc ((nFunCorr*nValCorr+1)*sizeof(double));

  // VISCOSITY
  indexAcf = (double *)malloc((nBuffAcf+1)*sizeof(double));
  viscAcf = (double **)malloc((nBuffAcf+1)*sizeof(double *));
  for(n = 0 ; n <= nBuffAcf ; n ++)
    viscAcf[n] = (double *)malloc((nValAcf+1)*sizeof(double ));
  viscAcfOrg = (double *)malloc((nBuffAcf+1)*sizeof(double));
  viscAcfAv = (double *)malloc((nValAcf+1)*sizeof(double));

  // RDF
  histRdf = (double *)malloc((sizeHistRdf+1)*sizeof(double)); 

}

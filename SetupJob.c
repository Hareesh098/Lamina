#include<stdio.h>
#include"globalExtern.h"
void AllocArrays();
void AccumProps(int icode);
void InitVacf();
void SetupJob(){
  AllocArrays();
  AccumProps(0);
  InitVacf();
  stepCount = 0;
  // INITIALISE SPACETIME CORRELATIONS
  int n;
  for (n = 1; n <= nBuffCorr; n++)
    indexCorr[n] = -(n - 1)*nValCorr/nBuffCorr;
  countCorrAv = 0.;
  for (n = 1; n <= nFunCorr*nValCorr; n++)
    spacetimeCorrAv[n] = 0.;

  //RDF
  countRdf = 0;
}

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
#include"global.h"

void EvalSpacetimeCorr (){
  real cosV=0., cosV0=0., cosV1=0., cosV2=0., sinV=0., sinV1=0., sinV2=0.;
  real COSA, SINA, COSV, SINV;
  int j, m, n, nb, ni, nv;
  real kMin = 2. * M_PI / region[1];
  real kMax = M_PI;
  real deltaK = (kMax - kMin) / nFunCorr;
  
  for (j = 1; j <= 2*nFunCorr; j++)
    cfVal[j] = 0.;

  for (n = 1; n <= nAtom; n++){
    j = 1;
    COSA = cos(kMin*rx[n]);
    SINA = sin(kMin*rx[n]);
    for (m = 1; m <= nFunCorr; m++){
      if(m == 1){
	cosV = cos(deltaK*rx[n]);
	sinV = sin(deltaK*rx[n]);
	cosV0 = cosV;
      }else if(m == 2){
	cosV1 = cosV;
	sinV1 = sinV;
	cosV = 2.*cosV0*cosV1-1;
	sinV = 2.*cosV0*sinV1;
      }else{
	cosV2 = cosV1;
	sinV2 = sinV1;
	cosV1 = cosV;
	sinV1 = sinV;
	cosV = 2.*cosV0*cosV1-cosV2;
	sinV = 2.*cosV0*sinV1-sinV2;
      }
      COSV = COSA*cosV - SINA*sinV;
      SINV = SINA*cosV + COSA*sinV;
      cfVal[j] += COSV;
      cfVal[j+1] += SINV;
      j += 2;
    }
  }

  for (nb = 1; nb <= nBuffCorr; nb++){
    indexCorr[nb] += 1;
    if (indexCorr[nb] <= 0) continue;
    ni = nFunCorr * (indexCorr[nb] - 1);
    if (indexCorr[nb] == 1){
      for (j = 1; j <= 2*nFunCorr; j++)
	cfOrg[nb][j] = cfVal[j];
    }

    for (j = 1; j <= nFunCorr; j++)
      spacetimeCorr[nb][ni + j] = 0.;
    
    j = 1;
    for (m = 1; m <= nFunCorr; m++){
      nv = m + ni;
      spacetimeCorr[nb][nv] += cfVal[j] * cfOrg[nb][j] + cfVal[j + 1] * cfOrg[nb][j + 1];
      j += 2;
    }

  }
  
  // ACCUMULATE SPACETIME CORRELATIONS
  for (nb = 1; nb <= nBuffCorr; nb++){
   if (indexCorr[nb] == nValCorr){
     for (j = 1; j <= nFunCorr*nValCorr; j++)
       spacetimeCorrAv[j] += spacetimeCorr[nb][j];
     indexCorr[nb] = 0.;
     countCorrAv ++;
     if (countCorrAv == limitCorrAv){
       for (j = 1; j <= nFunCorr*nValCorr; j++)
	 spacetimeCorrAv[j] /= (nAtom*limitCorrAv);
       fprintf(fpdnsty,"NDIM %d\n", NDIM);
       fprintf(fpdnsty,"nAtom %d\n", nAtom);
       fprintf(fpdnsty,"region %lf\n", region[1]);
       fprintf(fpdnsty,"nFunCorr %d\n", nFunCorr);
       fprintf(fpdnsty,"limitCorrAv %d\n", limitCorrAv);
       fprintf(fpdnsty,"stepCorr %d\n", stepCorr);
       fprintf(fpdnsty,"nValCorr %d\n", nValCorr);
       fprintf(fpdnsty,"deltaT %lf\n", deltaT);
       real tVal;
       for (n = 1; n <= nValCorr; n++){
   	 tVal = (n-1)*stepCorr*deltaT;
 	 fprintf (fpdnsty, "%e\t", tVal);
	 int nn = nFunCorr*(n-1);
   	 for (j = 1; j <= nFunCorr; j ++)
     	   fprintf (fpdnsty, "%e\t", spacetimeCorrAv[nn + j]);
     	 fprintf (fpdnsty, "\n");
       }    
       
       countCorrAv = 0.;
       for (j = 1; j <= nFunCorr*nValCorr; j++)
	 spacetimeCorrAv[j] = 0.;
     }
   }
  }
}

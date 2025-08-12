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
#include<stdlib.h>
#include"global.h"

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

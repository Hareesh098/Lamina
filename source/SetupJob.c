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
#include"global.h"

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

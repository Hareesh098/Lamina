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

void DumpPairs(){
  int n;
  //Trajectory file in LAMMPS dump format for OVITO visualization
  fprintf(fppair, "ITEM: TIMESTEP\n");
  fprintf(fppair, "%lf\n",timeNow);
  fprintf(fppair, "ITEM: NUMBER OF ENTRIES\n");
  fprintf(fppair, "%d\n",nPairActive);
  fprintf(fppair, "ITEM: BOX BOUNDS pp ff pp\n");
  fprintf(fppair, "%lf %lf xlo xhi\n", -regionH[1], regionH[1]);
  fprintf(fppair, "%lf %lf ylo yhi\n", -regionH[2], regionH[2]);
  fprintf(fppair, "%lf %lf zlo zhi\n", -0.1, 0.1);
  fprintf(fppair, "ITEM: ENTRIES index, atom1 atom2 xij yij discDragx1 discDragy1\n");

  for(n=1; n<=nPairActive; n++)
   fprintf(fppair, "%d %d %d %0.16lf %0.16lf %0.16lf %0.16lf\n", PairID[n], Pairatom1[n], Pairatom2[n], 
   PairXij[n], PairYij[n], discDragx[n], discDragy[n]);

  }




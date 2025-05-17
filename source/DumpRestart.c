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


#include <stdio.h>
#include "global.h"

void DumpRestart() {
 char DUMP[256];
 FILE *fpDUMP;
 sprintf(DUMP, "%s.Restart", prefix);
 fpDUMP = fopen(DUMP, "w");
 if(fpDUMP == NULL) {
  fprintf(stderr, "Error opening file %s for writing\n", DUMP);
  return;
 }

  fprintf(fpDUMP, "timeNow %lf\n", timeNow);
  fprintf(fpDUMP, "nAtom %d\n",  nAtom);
  fprintf(fpDUMP, "nBond %d\n", nBond);
  fprintf(fpDUMP, "nAtomType %d\n", nAtomType);
  fprintf(fpDUMP, "nBondType %d\n", nBondType);
  fprintf(fpDUMP, "region[1] %0.14lf\n", region[1]);
  fprintf(fpDUMP, "region[2] %0.14lf\n", region[2]);

  int n; 
  fprintf(fpDUMP, "Atoms\n");
  for(n = 1; n <= nAtom; n ++)
   fprintf(fpDUMP, "%d %d %d %0.2lf %0.16lf %0.16lf %0.16lf %0.16lf\n", atomID[n], molID[n], atomType[n], atomRadius[n], rx[n], ry[n], vx[n], vy[n]);
  

  fprintf(fpDUMP, "Bonds\n"); 
  for(n=1; n<=nBond; n++)
  fprintf(fpDUMP,  "%d %d %d %d %0.2lf %0.16lf\n", BondID[n], BondType[n], atom1[n], atom2[n], kb[n], ro[n]);

  fclose(fpDUMP);
}


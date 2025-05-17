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

void Trajectory(){
 int n;
 //Trajectory file in LAMMPS dump format for OVITO visualization
 fprintf(fpxyz, "ITEM: TIMESTEP\n");
 fprintf(fpxyz, "%lf\n",timeNow);
 fprintf(fpxyz, "ITEM: NUMBER OF ATOMS\n");
 fprintf(fpxyz, "%d\n",nAtom);
 fprintf(fpxyz, "ITEM: BOX BOUNDS pp ff pp\n");
 fprintf(fpxyz, "%lf %lf xlo xhi\n", -regionH[1], regionH[1]);
 fprintf(fpxyz, "%lf %lf ylo yhi\n", -regionH[2], regionH[2]);
 fprintf(fpxyz, "%lf %lf zlo zhi\n", -0.1, 0.1);
 fprintf(fpxyz, "ITEM: ATOMS id mol type radius x y vx vy fx fy\n");
 for(n=1; n<=nAtom; n++)
  fprintf(fpxyz, "%d\t %d\t %d\t %0.2lf\t %0.16lf\t %0.16lf\t %0.16lf\t %0.16lf\t %0.16lf\t %0.16lf\n", 
  atomID[n], molID[n], atomType[n], atomRadius[n], rx[n], ry[n], vx[n], vy[n], ax[n], ay[n]);
}




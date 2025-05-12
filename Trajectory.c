#include<stdio.h>
#include"globalExtern.h"
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




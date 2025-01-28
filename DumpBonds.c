#include<stdio.h>
#include"globalExtern.h"
void DumpBonds(){
  int n;
  //Trajectory file in LAMMPS dump format for OVITO visualization
  fprintf(fpbond, "ITEM: TIMESTEP\n");
  fprintf(fpbond, "%lf\n",timeNow);
  fprintf(fpbond, "ITEM: NUMBER OF ENTRIES\n");
  fprintf(fpbond, "%d\n",nBond);
  fprintf(fpbond, "ITEM: BOX BOUNDS pp ff pp\n");
  fprintf(fpbond, "%lf %lf xlo xhi\n", -regionH[1], regionH[1]);
  fprintf(fpbond, "%lf %lf ylo yhi\n", -regionH[2], regionH[2]);
  fprintf(fpbond, "%lf %lf zlo zhi\n", -0.1, 0.1);
  fprintf(fpbond, "ITEM: ENTRIES BondID, BondType, atom1 atom2 kb ro\n");

  for(n=1; n<=nBond; n++)
   fprintf(fpbond, "%d %d %d %d %lf %lf\n", BondID[n], BondType[n], atom1[n], atom2[n], kb[BondID[n]], ro[BondID[n]]);
  }




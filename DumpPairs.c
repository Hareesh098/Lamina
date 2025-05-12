#include<stdio.h>
#include"globalExtern.h"
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




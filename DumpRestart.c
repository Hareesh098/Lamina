#include <stdio.h>
#include "globalExtern.h"
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
   fprintf(fpDUMP, "%d %d %0.2lf %lf %lf %lf %lf\n", atomID[n], atomType[n], atomRadius[n], rx[n], ry[n], vx[n], vy[n]);
  

  fprintf(fpDUMP, "Bonds\n"); 
  for(n=1; n<=nBond; n++)
  fprintf(fpDUMP,  "%d %d %d %d\n", BondID[n], BondType[n], atom1[n], atom2[n]);

  fclose(fpDUMP);
}


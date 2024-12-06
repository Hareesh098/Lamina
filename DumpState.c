#include <stdio.h>
#include "globalExtern.h"
void DumpState() {
 char DUMP[256];
 FILE *fpDUMP;
 sprintf(DUMP, "%s.STATE", prefix);
 fpDUMP = fopen(DUMP, "w");
 if(fpDUMP == NULL) {
  fprintf(stderr, "Error opening file %s for writing\n", DUMP);
  return;
 }

  fprintf(fpDUMP, "ITEM: TIMESTEP\n");
  fprintf(fpDUMP, "%lf\n",timeNow);
  fprintf(fpDUMP, "ITEM: NUMBER OF ATOMS\n");
  fprintf(fpDUMP, "%d\n",nAtom);
  fprintf(fpDUMP, "ITEM: BOX BOUNDS pp pp pp\n");
  fprintf(fpDUMP, "%lf %lf xlo xhi\n", -regionH[1], regionH[1]);
  fprintf(fpDUMP, "%lf %lf ylo yhi\n", -regionH[1], regionH[1]);
  fprintf(fpDUMP, "%lf %lf zlo zhi\n", -regionH[1], regionH[1]);
  fprintf(fpDUMP, "ITEM: ATOMS id type radius x y vx vy fx fy\n");
  int n;
  for (n = 1; n <= nAtom; n++) {
   fprintf(fpDUMP, "%d\t %d\t %0.2lf\t %0.16lf\t %0.16lf\t %0.16lf\t %0.16lf\t %0.16lf\t %0.16lf\t\n",
    atomID[n], atomType[n], atomRadius[n], rx[n], ry[n], vx[n], vy[n], ax[n], ay[n] );
  }
  fclose(fpDUMP);
}


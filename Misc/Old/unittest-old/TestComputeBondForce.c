#include <stdio.h>
#include <math.h>
#include "../source/global.h"

void ComputeBondForce();
void TestComputeBondForce();

int main() {
 //nAtom = 3; 
 //nBond = 1;
 WrongFlag = 0; 
 int atomID[nAtom+1], atomType[nAtom+1];
 double atomRadius[nAtom+1], rx[nAtom+1], ry[nAtom+1], vx[nAtom+1], vy[nAtom+1];
 
 int BondID[nBond+1], BondType[nBond+1], atom1[nBond+1], atom2[nBond+1];
 double kb[nBond+1], ro[nBond+1];
 double BondLength[nBond+1], BondEnergy[nBond+1];
 
 // Atom data (initialize the global arrays)
 atomID[0] = 0; atomID[1] = 1; atomID[2] = 2; atomID[3] = 3;
 atomType[0] = 0; atomType[1] = 4; atomType[2] = 4; atomType[3] = 5;
 atomRadius[0] = 0.0; atomRadius[1] = 1.0; atomRadius[2] = 1.0; atomRadius[3] = 0.0;
 rx[0] = 0.0; rx[1] = -0.9; rx[2] = 1.0; rx[3] = 4.0;
 ry[0] = 0.0; ry[1] = 0.2; ry[2] = 0.0; ry[3] = 0.1;
 vx[0] = 0.0; vx[1] = 1.0; vx[2] = -0.37; vx[3] = 0.0;
 vy[0] = 0.0; vy[1] = -0.786; vy[2] = -0.086; vy[3] = 0.0;

 // Bond data (initialize the global arrays)
 BondID[0] = 0; BondID[1] = 1;
 BondType[0] = 0; BondType[1] = 1;
 atom1[0] = 0; atom1[1] = 2;
 atom2[0] = 0; atom2[1] = 3;
 kb[0] = 0.0; kb[1] = 1.00;
 ro[0] = 0.0; ro[1] = 3.1;
 printf("Environment set up.\n");

 for (int i = 0; i <= nBond; i++) {
  printf("i = %d\n",BondID[i]);
  }
  ComputeBondForce();
  printf("%d\n",rx[atom1[1]]);
 return 0;
}


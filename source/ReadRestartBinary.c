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
#include <stdlib.h>
#include <string.h>
#include"global.h"

// Must match RestartHeader definition in WriteBinaryRestart
typedef struct {
 char magic[8];         // "LAMINA\0"
 double version;
 double timeNow;
 int nAtom;
 int nBond;
 int nAtomType;
 int nBondType;
 double regionX;   // = region[1]
 double regionY;   // = region[2]
 int nAtomInterface;
 int nAtomBlock;
 int nDiscInterface;
 double bigDiameter;
 double InterfaceWidth;
 int nPairActive;
 int nPairTotal;
 double uSumPair;
 double virSumPair;
 double virSumPairxx;
 double virSumPairyy;
 double virSumPairxy;
 double TotalBondEnergy;
 double virSumBond;
 double virSumBondxx;
 double virSumBondyy;
 double virSumBondxy;
 int stepCount;
 double forceSumxExtern; 
 double forceSumyExtern;
} RestartHeader;

void ReadBinaryRestart(const char *filename) {
 
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "Error opening binary restart file %s for reading\n", filename);
    exit(EXIT_FAILURE);
  }
  RestartHeader hdr;  //Declare here
  fread(&hdr, sizeof(RestartHeader), 1, fp);   //Use it

  if(strncmp(hdr.magic, "LAMINA", 6) != 0) {
   fprintf(stderr, "Invalid file format: magic = %.8s [from %s()]\n", hdr.magic, __func__);
   fclose(fp);
   exit(EXIT_FAILURE);  //Must return void, not return 1
  }
  
  //Now assigned the values that were read from binary file to global parameters
  timeNow = hdr.timeNow;
  nAtom = hdr.nAtom;
  nBond = hdr.nBond;
  nAtomType = hdr.nAtomType;
  nBondType = hdr.nBondType;
  region[1] = hdr.regionX;
  region[2] = hdr.regionY;
  nAtomInterface = hdr.nAtomInterface;
  nAtomBlock = hdr.nAtomBlock;
  nDiscInterface = hdr.nDiscInterface;
  bigDiameter = hdr.bigDiameter;
  InterfaceWidth = hdr.InterfaceWidth;
  nPairActive = hdr.nPairActive;
  nPairTotal = hdr.nPairTotal;
  uSumPair = hdr.uSumPair;
  virSumPair = hdr.virSumPair;
  virSumPairxx = hdr.virSumPairxx;
  virSumPairyy = hdr.virSumPairyy;
  virSumPairxy = hdr.virSumPairxy;
  TotalBondEnergy = hdr.TotalBondEnergy;
  virSumBond = hdr.virSumBond;
  virSumBondxx = hdr.virSumBondxx;
  virSumBondyy = hdr.virSumBondyy;
  virSumBondxy = hdr.virSumBondxy;
  stepCount = hdr.stepCount;
  forceSumxExtern = hdr.forceSumxExtern;
  forceSumyExtern = hdr.forceSumyExtern;
 
  density = nAtom / (region[1] * region[2]);
  cells[1] = region[1] / rCut;
  cells[2] = region[2] / rCut;
  regionH[1] = 0.5 * region[1];
  regionH[2] = 0.5 * region[2];

  cellList = (int *)malloc((nAtom + cells[1] * cells[2] + 1) * sizeof(int));
  
  printf("Running from restart file:\n");
  printf("Running: %s, version: %0.3lf\n", hdr.magic, hdr.version);
  printf("timeNow: %lf\n", timeNow);
  printf("stepCount: %d\n", stepCount);  

  //Allocating the memory to arrays  
  atomID = (int *)malloc((nAtom + 1) * sizeof(int));
  molID = (int *)malloc((nAtom + 1) * sizeof(int));
  atomType = (int *)malloc((nAtom + 1) * sizeof(int));
  atomRadius = (double *)malloc((nAtom + 1) * sizeof(double));
  rx = (double *)malloc((nAtom + 1) * sizeof(double));
  ry = (double *)malloc((nAtom + 1) * sizeof(double));
  vx = (double *)malloc((nAtom + 1) * sizeof(double));
  vy = (double *)malloc((nAtom + 1) * sizeof(double));
  ax = (double *)malloc((nAtom + 1) * sizeof(double));
  ay = (double *)malloc((nAtom + 1) * sizeof(double));
  fx = (double *)malloc((nAtom + 1) * sizeof(double));
  fy = (double *)malloc((nAtom + 1) * sizeof(double));
  atomMass = (double *)malloc((nAtom + 1) * sizeof(double));
  discDragx = (double *)malloc((nAtom + 1) * sizeof(double));
  discDragy = (double *)malloc((nAtom + 1) * sizeof(double));
  atomIDInterface = (int *)malloc((nAtom + 1) * sizeof(int));
  
  BondID = (int *)malloc((nBond + 1) * sizeof(int));
  BondType = (int *)malloc((nBond + 1) * sizeof(int));
  atom1 = (int *)malloc((nBond + 1) * sizeof(int));
  atom2 = (int *)malloc((nBond + 1) * sizeof(int));
  kb = (double *)malloc((nBond + 1) * sizeof(double));
  ro = (double *)malloc((nBond + 1) * sizeof(double));
  BondEnergy = (double *)malloc((nBond + 1) * sizeof(double));
  BondLength = (double *)malloc((nBond + 1) * sizeof(double));
  nodeDragx = (double *)malloc((nAtom + 1) * sizeof(double));
  nodeDragy = (double *)malloc((nAtom + 1) * sizeof(double));
  rxUnwrap = (double *)malloc((nAtom + 1) * sizeof(double));
  ryUnwrap = (double *)malloc((nAtom + 1) * sizeof(double));
  ImageX = (int *)malloc((nAtom + 1) * sizeof(int));
  ImageY = (int *)malloc((nAtom + 1) * sizeof(int));

  PairID = (int *)malloc((nPairTotal + 1) * sizeof(int));
  Pairatom1 = (int *)malloc((nPairTotal + 1) * sizeof(int));
  Pairatom2 = (int *)malloc((nPairTotal + 1) * sizeof(int));
  PairXij = (double *)malloc((nPairTotal + 1) * sizeof(double));
  PairYij = (double *)malloc((nPairTotal + 1) * sizeof(double));
  
 //Here we are reading the data to binary file
 fread(&atomID[1], sizeof(int), nAtom, fp); 
 fread(&molID[1], sizeof(int), nAtom, fp); 
 fread(&atomType[1], sizeof(int), nAtom, fp); 
 fread(&atomRadius[1], sizeof(double), nAtom, fp); 
 fread(&rx[1], sizeof(double), nAtom, fp); 
 fread(&ry[1], sizeof(double), nAtom, fp); 
 fread(&vx[1], sizeof(double), nAtom, fp); 
 fread(&vy[1], sizeof(double), nAtom, fp); 
 fread(&ax[1], sizeof(double), nAtom, fp); 
 fread(&ay[1], sizeof(double), nAtom, fp);
 fread(&fx[1], sizeof(double), nAtom, fp); 
 fread(&fy[1], sizeof(double), nAtom, fp); 
 fread(&atomMass[1], sizeof(double), nAtom, fp);
 fread(&discDragx[1], sizeof(double), nAtom, fp);
 fread(&discDragy[1], sizeof(double), nAtom, fp);
 fread(&atomIDInterface[1], sizeof(int), nAtomInterface, fp); 
 
 fread(&BondID[1], sizeof(int), nBond, fp);
 fread(&BondType[1], sizeof(int), nBond, fp);
 fread(&atom1[1], sizeof(int), nBond, fp);
 fread(&atom2[1], sizeof(int), nBond, fp);
 fread(&kb[1], sizeof(double), nBond, fp);
 fread(&ro[1], sizeof(double), nBond, fp); 
 fread(&BondEnergy[1], sizeof(double), nBond, fp);
 fread(&BondLength[1], sizeof(double), nBond, fp);    
 fread(&nodeDragx[1], sizeof(double), nAtom, fp);
 fread(&nodeDragy[1], sizeof(double), nAtom, fp);
 fread(&rxUnwrap[1], sizeof(double), nAtom, fp);
 fread(&ryUnwrap[1], sizeof(double), nAtom, fp);
 fread(&ImageX[1], sizeof(int), nAtom, fp); 
 fread(&ImageY[1], sizeof(int), nAtom, fp); 
 
 fread(&PairID[1], sizeof(int), nPairActive, fp);
 fread(&Pairatom1[1], sizeof(int), nPairActive, fp);
 fread(&Pairatom2[1], sizeof(int), nPairActive, fp);
 fread(&PairXij[1], sizeof(double), nPairActive, fp);
 fread(&PairYij[1], sizeof(double), nPairActive, fp);
 
 //2D-List of bonded atoms. This is used to remove pair interaction
 //calculation for the bonded atoms
 isBonded = (int **)malloc((nAtom + 1) * sizeof(int*));
 for (int i = 0; i <= nAtom; i++) {
  isBonded[i] = (int *)malloc((nAtom + 1) * sizeof(int));
  for (int j = 0; j <= nAtom; j++) {
  isBonded[i][j] = 0;
  } }
  for (int n = 1; n <= nBond; n++) {
   int i = atom1[n];
   int j = atom2[n];
   isBonded[i][j] = 1;
   isBonded[j][i] = 1; // symmetric
}

  fprintf(fpresult, "------------------------------------\n");
  fprintf(fpresult, "-------PARAMETERS-----------\n");
  fprintf(fpresult, "------------------------------------\n");
  fprintf(fpresult, "nAtom\t\t\t%d\n",  nAtom);
  fprintf(fpresult, "nBond\t\t\t%d\n",  nBond);
  fprintf(fpresult, "nAtomType\t\t%d\n", nAtomType);
  fprintf(fpresult, "nBondType\t\t%d\n",  nBondType);
  fprintf(fpresult, "nAtomBlock\t\t%d\n",  nAtomBlock);
  fprintf(fpresult, "nAtomInterface\t\t%d\n",  nAtomInterface);
  fprintf(fpresult, "nDiscInterface\t\t%d\n",  nDiscInterface);
  fprintf(fpresult, "mass\t\t\t%0.6g\n", mass);
  fprintf(fpresult, "gamman\t\t\t%0.6g\n", gamman);
  fprintf(fpresult, "strain\t\t\t%0.6g\n", strain);
  fprintf(fpresult, "strainRate\t\t%0.6g\n", strainRate);
  fprintf(fpresult, "FyBylx\t\t\t%0.6g\n", FyBylx);
  fprintf(fpresult, "fxByfy\t\t\t%0.6g\n", fxByfy);
  fprintf(fpresult, "DeltaY\t\t\t%0.6g\n", DeltaY);
  fprintf(fpresult, "DeltaX\t\t\t%0.6g\n", DeltaX);
  fprintf(fpresult, "HaltCondition\t\t%0.6g\n", HaltCondition);
  fprintf(fpresult, "kappa\t\t\t%g\n", kappa);
  fprintf(fpresult, "density\t\t\t%g\n", density);
  fprintf(fpresult, "rCut\t\t\t%g\n", rCut);
  fprintf(fpresult, "deltaT\t\t\t%g\n", deltaT);
  fprintf(fpresult, "stepEquil\t\t%d\n",  stepEquil);
  fprintf(fpresult, "stepLimit\t\t%d\n",  stepLimit);
  fprintf(fpresult, "region[1]\t\t%0.16lf\n", region[1]);
  fprintf(fpresult, "region[2]\t\t%0.16lf\n", region[2]);
  fprintf(fpresult, "cells[1]\t\t%d\n",  cells[1]);
  fprintf(fpresult, "cells[2]\t\t%d\n",  cells[2]);
  fprintf(fpresult, "solver\t\t\t%s\n",  solver);
  fprintf(fpresult, "boundary\t\t%s %s\n", xBoundary, yBoundary);
  fprintf(fpresult, "DampFlag\t\t%d\n",  DampFlag);
  fprintf(fpresult, "------------------------------------\n");
  fprintf(fpresult, "#TimeNow TotalMomentum PotEngyPerAtom KinEngyPerAtom TotEngyPerAtom PairEnergyPerAtom BondEnergyPerAtom  Press VirialSum\n");
  fprintf(fpvrms, "#timeNow\tVrms \n");
  fprintf(fpcom, "#timeNow\tComX\tComY\n");
  fprintf(fpforce, "#timeNow\tforceSumxAtomType1\tforceSumyAtomType1\tforceSumxAtomType2\tforceSumyAtomType2\tforceSumxAtomType3\tforceSumyAtomType3\tforceSumxAtomType4\tforceSumyAtomType4\tforceSumxAtomType5\tforceSumyAtomType5\tforceSumxExtern\tforceSumyExtern\n");
  fclose(fp);
 }


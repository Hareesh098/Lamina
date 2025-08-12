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
#include "global.h"

// Header struct must match that of WriteRestartBinary
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

void WriteBinaryRestart() {
 RestartHeader hdr = {
 .magic = "LAMINA",
 .version = 1.0,
 .timeNow = timeNow,
 .nAtom = nAtom,
 .nBond = nBond,
 .nAtomType = nAtomType,
 .nBondType = nBondType,
 .regionX = region[1],
 .regionY = region[2],
 .nAtomInterface = nAtomInterface,
 .nAtomBlock = nAtomBlock,
 .nDiscInterface = nDiscInterface,
 .bigDiameter = bigDiameter,
 .InterfaceWidth = InterfaceWidth,
 .nPairActive = nPairActive,
 .nPairTotal = nPairTotal,
 .uSumPair = uSumPair,
 .virSumPair = virSumPair,
 .virSumPairxx = virSumPairxx,
 .virSumPairyy = virSumPairyy,
 .virSumPairxy = virSumPairxy,
 .TotalBondEnergy = TotalBondEnergy,
 .virSumBond = virSumBond,
 .virSumBondxx = virSumBondxx,
 .virSumBondyy = virSumBondyy,
 .virSumBondxy = virSumBondxy,
 .stepCount = stepCount,
 .forceSumxExtern = forceSumxExtern, 
 .forceSumyExtern = forceSumyExtern
 };

 char DUMP[256];
 FILE *fp;
 sprintf(DUMP, "%s.bin", prefix);  // Produces e.g. "../output/test.bin"
 fp = fopen(DUMP, "wb");
 if (!fp) {
 fprintf(stderr, "Error opening binary restart file %s for writing\n", DUMP);
 exit(EXIT_FAILURE);
 }
 
 //Here we are writing the data to binary file
 fwrite(&hdr, sizeof(RestartHeader), 1, fp);
 fwrite(&atomID[1], sizeof(int), nAtom, fp); 
 fwrite(&molID[1], sizeof(int), nAtom, fp); 
 fwrite(&atomType[1], sizeof(int), nAtom, fp); 
 fwrite(&atomRadius[1], sizeof(double), nAtom, fp); 
 fwrite(&rx[1], sizeof(double), nAtom, fp); 
 fwrite(&ry[1], sizeof(double), nAtom, fp); 
 fwrite(&vx[1], sizeof(double), nAtom, fp); 
 fwrite(&vy[1], sizeof(double), nAtom, fp); 
 fwrite(&ax[1], sizeof(double), nAtom, fp); 
 fwrite(&ay[1], sizeof(double), nAtom, fp); 
 fwrite(&fx[1], sizeof(double), nAtom, fp); 
 fwrite(&fy[1], sizeof(double), nAtom, fp); 
 fwrite(&atomMass[1], sizeof(double), nAtom, fp);
 fwrite(&discDragx[1], sizeof(double), nAtom, fp);
 fwrite(&discDragy[1], sizeof(double), nAtom, fp);
 fwrite(&atomIDInterface[1], sizeof(int), nAtomInterface, fp); 
 
 fwrite(&BondID[1], sizeof(int), nBond, fp);
 fwrite(&BondType[1], sizeof(int), nBond, fp);
 fwrite(&atom1[1], sizeof(int), nBond, fp);
 fwrite(&atom2[1], sizeof(int), nBond, fp);
 fwrite(&kb[1], sizeof(double), nBond, fp);
 fwrite(&ro[1], sizeof(double), nBond, fp); 
 fwrite(&BondEnergy[1], sizeof(double), nBond, fp);
 fwrite(&BondLength[1], sizeof(double), nBond, fp);    
 fwrite(&nodeDragx[1], sizeof(double), nAtom, fp);
 fwrite(&nodeDragy[1], sizeof(double), nAtom, fp);
 fwrite(&rxUnwrap[1], sizeof(double), nAtom, fp);
 fwrite(&ryUnwrap[1], sizeof(double), nAtom, fp);
 fwrite(&ImageX[1], sizeof(int), nAtom, fp); 
 fwrite(&ImageY[1], sizeof(int), nAtom, fp); 

 fwrite(&PairID[1], sizeof(int), nPairActive, fp);
 fwrite(&Pairatom1[1], sizeof(int), nPairActive, fp);
 fwrite(&Pairatom2[1], sizeof(int), nPairActive, fp);
 fwrite(&PairXij[1], sizeof(double), nPairActive, fp);
 fwrite(&PairYij[1], sizeof(double), nPairActive, fp);

 fclose(fp);
}


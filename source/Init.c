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
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include"global.h"

void ReadBinaryRestart(const char *filename);

void Init() {
 char dummy[128];

 // Always read input parameters
 FILE *fp = fopen("input-data", "r");
 if(!fp) {
  perror("input-data");
  exit(EXIT_FAILURE);
 }
  
  fscanf(fp, "%s %s", mode, inputConfig);  // config type + filename
  fscanf(fp, "%s %s", dummy, solver);
  fscanf(fp, "%s %s %s", dummy, xBoundary, yBoundary);
  fscanf(fp, "%s %d",  dummy, &DampFlag);
  fscanf(fp, "%s %d",  dummy, &freezeAtomType);
  fscanf(fp, "%s %lf", dummy, &rCut);
  fscanf(fp, "%s %lf", dummy, &Kn);
  fscanf(fp, "%s %lf", dummy, &mass);
  fscanf(fp, "%s %lf", dummy, &gamman); 
  fscanf(fp, "%s %lf", dummy, &kappa);
  fscanf(fp, "%s %lf", dummy, &deltaT);
  fscanf(fp, "%s %lf", dummy, &strain);
  fscanf(fp, "%s %lf", dummy, &gravField);
  fscanf(fp, "%s %lf", dummy, &FyBylx);
  fscanf(fp, "%s %lf", dummy, &fxByfy);
  fscanf(fp, "%s %lf", dummy, &DeltaY);
  fscanf(fp, "%s %lf", dummy, &DeltaX);
  fscanf(fp, "%s %lf", dummy, &HaltCondition);
  fscanf(fp, "%s %d",  dummy, &stepAvg);
  fscanf(fp, "%s %d",  dummy, &stepEquil);
  fscanf(fp, "%s %d",  dummy, &stepLimit);
  fscanf(fp, "%s %d",  dummy, &stepDump);
  fscanf(fp, "%s %d",  dummy, &stepTraj);
  fscanf(fp, "%s %d",  dummy, &limitCorrAv);
  fscanf(fp, "%s %d",  dummy, &nBuffCorr);
  fscanf(fp, "%s %d",  dummy, &nFunCorr);
  fscanf(fp, "%s %d",  dummy, &nValCorr);
  fscanf(fp, "%s %d",  dummy, &stepCorr);
  fscanf(fp, "%s %d",  dummy, &limitAcfAv);
  fscanf(fp, "%s %d",  dummy, &nBuffAcf);
  fscanf(fp, "%s %d",  dummy, &nValAcf);
  fscanf(fp, "%s %d",  dummy, &stepAcf);
  fscanf(fp, "%s %lf", dummy, &rangeRdf);
  fscanf(fp, "%s %d",  dummy, &limitRdf);
  fscanf(fp, "%s %d",  dummy, &sizeHistRdf);
  fscanf(fp, "%s %d",  dummy, &stepRdf);
  fclose(fp);
  
  int useBinaryRestart = 0;
  if(strcmp(mode, "read_restart") == 0) {
   useBinaryRestart = 1;
  } else if (strcmp(mode, "read_data") != 0) {
   fprintf(stderr, "ERROR: First line of input-data must be 'read_data' or 'read_restart'\n");
   exit(0);
  }
    
  //Conditionally read binary config
  if(useBinaryRestart) {
   ReadBinaryRestart(inputConfig);  // uses global prefix + config file
   printf(">>> Binary restart loaded from %s <<<\n", inputConfig);
   printf(">>> Restarting simulation from time = %.8lf <<<\n", timeNow);
   return; //Exiting from Init() from here 
  }
  
  FILE *fpSTATE;
  if((fpSTATE = fopen(inputConfig,"r"))==NULL){
  printf("Error occurred: Could not open STATE file\n Exiting now..\n");
  exit(0);
  }

  if(fscanf(fpSTATE, "%s %lf", dummy, &timeNow) != 2 || strcmp(dummy, "timeNow") != 0) {
   fprintf(stderr, "ERROR [%s:%d:%s]: Expected 'timeNow <value>' as the first line in the config file.\n",
   __FILE__, __LINE__, __func__);
   exit(EXIT_FAILURE);
  }

  if(timeNow == 0.0) {
   printf(">>> Running from time = 0.0: Beginning of the simulation <<<\n");
   stepCount = 0;
  } 
  
  fscanf(fpSTATE, "%s %d",  dummy, &nAtom);
  fscanf(fpSTATE, "%s %d",  dummy, &nBond);
  fscanf(fpSTATE, "%s %d",  dummy, &nAtomType);
  fscanf(fpSTATE, "%s %d",  dummy, &nBondType);
  fscanf(fpSTATE, "%s %lf", dummy, &region[1]);
  fscanf(fpSTATE, "%s %lf", dummy, &region[2]);
  
  if(timeNow == 0.0)  region[2] *= 1.5; //Remove this when put on GitHub

  density = nAtom/(region[1]*region[2]); 
  cells[1] = region[1] / rCut;
  cells[2] = region[2] / rCut;
  cellList = (int*)malloc((nAtom + cells[1] * cells[2] + 1) * sizeof(int));
  regionH[1] = 0.5*region[1];
  regionH[2] = 0.5*region[2];

  //strain information
  strainRate = strain/deltaT;
  shearDisplacement = strain * region[2];
  shearVelocity = strainRate * region[2];
  int n;

  rx = (double*)malloc((nAtom + 1) * sizeof(double));
  ry = (double*)malloc((nAtom + 1) * sizeof(double));
  vx = (double*)malloc((nAtom + 1) * sizeof(double));
  vy = (double*)malloc((nAtom + 1) * sizeof(double));
  ax = (double*)malloc((nAtom + 1) * sizeof(double));
  ay = (double*)malloc((nAtom + 1) * sizeof(double));
  fx = (double*)malloc((nAtom + 1) * sizeof(double));
  fy = (double*)malloc((nAtom + 1) * sizeof(double));
  fax = (double*)malloc((nAtom + 1) * sizeof(double));
  fay = (double*)malloc((nAtom + 1) * sizeof(double));
  atomID = (int*)malloc((nAtom+1) * sizeof(int));
  atomType = (int*)malloc((nAtom+1) * sizeof(int));
  atomRadius = (double*)malloc((nAtom + 1) * sizeof(double));
  atomMass = (double*)malloc((nAtom + 1) * sizeof(double));
  speed = (double*)malloc((nAtom + 1) * sizeof(double));
  discDragx = (double*)malloc((nAtom + 1) * sizeof(double)); 
  discDragy = (double*)malloc((nAtom + 1) * sizeof(double)); 
  molID = (int*)malloc((nAtom+1) * sizeof(int));
    
  BondID = (int*)malloc((nBond+1)*sizeof(int));
  BondType = (int*)malloc((nBond+1)*sizeof(int));
  atom1 = (int*)malloc((nBond+1)*sizeof(int));
  atom2 = (int*)malloc((nBond+1)*sizeof(int)); 
  kb = (double*)malloc((nBond+1)*sizeof(double));
  ro = (double*)malloc((nBond+1)*sizeof(double));
  BondEnergy = (double*)malloc((nBond+1)*sizeof(double));
  BondLength =(double*)malloc((nBond+1)*sizeof(double));
  nodeDragx = (double*)malloc((nAtom + 1) * sizeof(double));
  nodeDragy = (double*)malloc((nAtom + 1) * sizeof(double));
  rxUnwrap = (double*)malloc((nAtom + 1) * sizeof(double));
  ryUnwrap = (double*)malloc((nAtom + 1) * sizeof(double));
  ImageX = (int*)malloc((nAtom+1) * sizeof(int));
  ImageY = (int*)malloc((nAtom+1) * sizeof(int));


  for(n = 1; n <= nAtom; n ++){
   atomMass[n] = mass;
  }
 
  fscanf(fpSTATE, "%s\n", dummy);
  for(n = 1; n <= nAtom; n ++)
   fscanf(fpSTATE, "%d %d %d %lf %lf %lf %lf %lf\n", &atomID[n], &molID[n], &atomType[n], &atomRadius[n], &rx[n], &ry[n], &vx[n], &vy[n]);
   

  fscanf(fpSTATE, "%s\n", dummy); 
  for(n=1; n<=nBond; n++)
   fscanf(fpSTATE, "%d %d %d %d %lf %lf\n", &BondID[n], &BondType[n], &atom1[n], &atom2[n], &kb[n], &ro[n]);

  fclose(fpSTATE);

 //2D-List of bonded atoms. This is used to remove pair interaction
 //calculation for the bonded atoms
   isBonded = (int**)malloc((nAtom + 1) * sizeof(int*));
  for (int i = 0; i <= nAtom; i++) {
    isBonded[i] = (int*)malloc((nAtom + 1) * sizeof(int));
    for (int j = 0; j <= nAtom; j++) {
        isBonded[i][j] = 0;
    }
  }
  
  for (n = 1; n <= nBond; n++) {
    int i = atom1[n];
    int j = atom2[n];
    isBonded[i][j] = 1;
    isBonded[j][i] = 1; // symmetric
}

 // List the interface atoms
 nAtomInterface = 0;
 nAtomBlock = 0;
 nDiscInterface = 0;
 bigDiameter = 2.8;
 InterfaceWidth = 5.0 * bigDiameter;

 for(n = 1; n <= nAtom; n++){
  if(fabs(ry[n]) < InterfaceWidth){
  nAtomInterface++;
  }
  if(molID[n] == 2){
  nAtomBlock++;
  } 
  if(atomRadius[n] != 0.0){
  nDiscInterface++;
  } } 

  
  int BondPairInteract;
  BondPairInteract = 0;
  int m;
  if(BondPairInteract == 1){
   atomIDInterface =  (int *)malloc((nAtomInterface+1)*sizeof(int));
   m = 1;
   for(n=1; n<=nAtom; n++){
    if(fabs(ry[n]) < InterfaceWidth){
    atomIDInterface[m] = atomID[n]; 
    m++; 
  } } }
  else if(BondPairInteract == 0){
   nAtomInterface = nDiscInterface;
   atomIDInterface =  (int *)malloc((nAtomInterface+1)*sizeof(int));
   m = 1;
   for(n=1; n<=nAtom; n++){
    if(atomRadius[n] != 0.0){
    atomIDInterface[m] = atomID[n]; 
    m++; 
  } } }

   // Defining the external forces
   double lx = regionH[1];
   if (FyBylx != 0 && gravField != 0) {
    fprintf(stderr, "Error: Both FyBylx and gravField cannot be nonzero simultaneously.\n");
    exit(EXIT_FAILURE);
   }
   if(FyBylx != 0) {
    // Case 1: External force defined via FyBylx
    fyExtern = (FyBylx * lx) / nAtomBlock;
   }
   else if (gravField != 0) {
   // Case 2: External force defined via gravField
    fyExtern  = mass * gravField;
    fxExtern  = fxByfy * fyExtern;
    FyBylx    = (fyExtern * nAtomBlock) / lx;
   } 
   else {
    // Case 3: No external force provided
    fyExtern = 0.0;
    fxExtern = 0.0;
  }

  nPairTotal = 0.5 * nAtomInterface * (nAtomInterface-1);
  PairID = (int*)malloc((nPairTotal+1) * sizeof(int));
  Pairatom1 = (int*)malloc((nPairTotal+1) * sizeof(int));
  Pairatom2 = (int*)malloc((nPairTotal+1) * sizeof(int));
  PairXij = (double*)malloc((nPairTotal+1) * sizeof(double));
  PairYij = (double*)malloc((nPairTotal+1) * sizeof(double));
  
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
  fprintf(fpresult, "mass\t\t\t%0.16g\n", mass);
  fprintf(fpresult, "gamman\t\t\t%0.16g\n", gamman);
  fprintf(fpresult, "strain\t\t\t%0.16g\n", strain);
  fprintf(fpresult, "strainRate\t\t%0.16g\n", strainRate);
  fprintf(fpresult, "gravField\t\t%0.16g\n", gravField);
  fprintf(fpresult, "FyBylx\t\t\t%0.16g\n", FyBylx);
  fprintf(fpresult, "fxByfy\t\t\t%0.16g\n", fxByfy);
  fprintf(fpresult, "DeltaY\t\t\t%0.16g\n", DeltaY);
  fprintf(fpresult, "DeltaX\t\t\t%0.16g\n", DeltaX);
  fprintf(fpresult, "HaltCondition\t\t%0.16g\n", HaltCondition);
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

/* //Uncomment the following as per your acquirement
    fprintf(fpstress, "strain           %lf\n", strain);
    fprintf(fpstress, "region[1]        %lf\n", region[1]);
    fprintf(fpstress, "region[2]        %lf\n", region[2]);
    fprintf(fpstress, "#timeNow virSumxx virSumyy virSumxy pressure\n");
    fprintf(fpmomentum, "#timeNow Px Py\n");
*/
  
   if((strcmp(xBoundary, "p") != 0 && strcmp(xBoundary, "r") != 0) ||
    (strcmp(yBoundary, "p") != 0 && strcmp(yBoundary, "r") != 0)) {
    fprintf(fpresult, "Error: Invalid boundary value detected: '%s %s'. Only 'p' or 'r' are allowed.\n", xBoundary, yBoundary);
    exit(EXIT_FAILURE); // Exit with failure status
  }

}

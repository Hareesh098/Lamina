#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include"globalExtern.h"
double perturb() {
    return ((double)rand() / RAND_MAX) * 0.02 - 0.01;
}

void Init(){
  char dummy[128];
  char inputConfig[128];
  FILE *fp;
  fp = fopen("input-data","r");
  fscanf(fp, "%s %s", dummy, inputConfig);
  fscanf(fp, "%s %s", dummy, solver);
  fscanf(fp, "%s %s %s", dummy, xBoundary, yBoundary);
  fscanf(fp, "%s %d", dummy, &freezeAtomType);
  fscanf(fp, "%s %lf", dummy, &rCut);
  fscanf(fp, "%s %lf", dummy, &kappa);
  fscanf(fp, "%s %lf", dummy, &deltaT);
  fscanf(fp, "%s %lf", dummy, &strain);
  fscanf(fp, "%s %lf", dummy, &forceY);
  fscanf(fp, "%s %lf", dummy, &forceX);
  fscanf(fp, "%s %lf", dummy, &DeltaY);
  fscanf(fp, "%s %lf", dummy, &DeltaX);
  fscanf(fp, "%s %lf", dummy, &HaltCondition);
  fscanf(fp, "%s %d", dummy, &stepAvg);
  fscanf(fp, "%s %d", dummy, &stepEquil);
  fscanf(fp, "%s %d", dummy, &stepLimit);
  fscanf(fp, "%s %d", dummy, &stepDump);
  fscanf(fp, "%s %d", dummy, &stepTraj);
  fscanf(fp, "%s %d", dummy, &limitCorrAv);
  fscanf(fp, "%s %d", dummy, &nBuffCorr);
  fscanf(fp, "%s %d", dummy, &nFunCorr);
  fscanf(fp, "%s %d", dummy, &nValCorr);
  fscanf(fp, "%s %d", dummy, &stepCorr);
  fscanf(fp, "%s %d", dummy, &limitAcfAv);
  fscanf(fp, "%s %d", dummy, &nBuffAcf);
  fscanf(fp, "%s %d", dummy, &nValAcf);
  fscanf(fp, "%s %d", dummy, &stepAcf);
  fscanf(fp, "%s %lf", dummy, &rangeRdf);
  fscanf(fp, "%s %d", dummy, &limitRdf);
  fscanf(fp, "%s %d", dummy, &sizeHistRdf);
  fscanf(fp, "%s %d", dummy, &stepRdf);

  fclose(fp);
  FILE *fpSTATE;
  if((fpSTATE = fopen(inputConfig,"r"))==NULL){
  printf("Error occurred: Could not open STATE file\n Exiting now..\n");
  exit(0);
  }

  fscanf(fpSTATE, "%s %lf", dummy, &timeNow);
  fscanf(fpSTATE, "%s %d",  dummy, &nAtom);
  fscanf(fpSTATE, "%s %d",  dummy, &nBond);
  fscanf(fpSTATE, "%s %d",  dummy, &nAtomType);
  fscanf(fpSTATE, "%s %d",  dummy, &nBondType);
  fscanf(fpSTATE, "%s %lf", dummy, &region[1]);
  fscanf(fpSTATE, "%s %lf", dummy, &region[2]);

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

  rx = (double*)malloc((nAtom + 1) * sizeof(double));
  ry = (double*)malloc((nAtom + 1) * sizeof(double));
  vx = (double*)malloc((nAtom + 1) * sizeof(double));
  vy = (double*)malloc((nAtom + 1) * sizeof(double));
  ax = (double*)malloc((nAtom + 1) * sizeof(double));
  ay = (double*)malloc((nAtom + 1) * sizeof(double));
  fax = (double*)malloc((nAtom + 1) * sizeof(double));
  fay = (double*)malloc((nAtom + 1) * sizeof(double));
  atomID = (int*)malloc((nAtom+1) * sizeof(int));
  atomType = (int*)malloc((nAtom+1) * sizeof(int));
  atomRadius = (double*)malloc((nAtom + 1) * sizeof(double));
  atomMass = (double*)malloc((nAtom + 1) * sizeof(double));
  speed = (double*)malloc((nAtom + 1) * sizeof(double));
  atom1 = (int*)malloc((nBond+1)*sizeof(int));
  atom2 = (int*)malloc((nBond+1)*sizeof(int)); 
  BondID = (int*)malloc((nBond+1)*sizeof(int));
  BondType = (int*)malloc((nBond+1)*sizeof(int));
  kb = (double*)malloc((nBond+1)*sizeof(double));
  ro = (double*)malloc((nBond+1)*sizeof(double));
  BondEnergy = (double*)malloc((nBond+1)*sizeof(double));
  BondLength =(double*)malloc((nBond+1)*sizeof(double));
  discDragx = (double*)malloc((nAtom + 1) * sizeof(double)); 
  discDragy = (double*)malloc((nAtom + 1) * sizeof(double)); 
  nodeDragx = (double*)malloc((nBond + 1) * sizeof(double));
  nodeDragy = (double*)malloc((nBond + 1) * sizeof(double));
  ImageX = (int*)malloc((nAtom+1) * sizeof(int));
  ImageY = (int*)malloc((nAtom+1) * sizeof(int));
  rxUnwrap = (double*)malloc((nAtom + 1) * sizeof(double));
  ryUnwrap = (double*)malloc((nAtom + 1) * sizeof(double));
   
  int n;
  for(n = 1; n <= nAtom; n ++){
   atomMass[n] = 1.0;
  }
  fscanf(fpSTATE, "%s\n", dummy);
  for(n = 1; n <= nAtom; n ++)
   fscanf(fpSTATE, "%d %d %lf %lf %lf %lf %lf\n", &atomID[n], &atomType[n], &atomRadius[n], &rx[n], &ry[n], &vx[n], &vy[n]);
  
  
  fscanf(fpSTATE, "%s\n", dummy); 
  for(n=1; n<=nBond; n++)
   fscanf(fpSTATE, "%d %d %d %d %lf %lf\n", &BondID[n], &BondType[n], &atom1[n], &atom2[n], &kb[n], &ro[n]);

  fclose(fpSTATE);
  

    fprintf(fpresult, "------------------------------------\n");
    fprintf(fpresult, "------------ PARAMETERS ------------\n");
    fprintf(fpresult, "------------------------------------\n");
    fprintf(fpresult, "nAtom            %d\n",  nAtom);
    fprintf(fpresult, "nBond            %d\n",  nBond);
    fprintf(fpresult, "strain           %lf\n", strain);
    fprintf(fpresult, "strainRate       %lf\n", strainRate);
    fprintf(fpresult, "forceY		%lf\n", forceY);
    fprintf(fpresult, "forceX		%lf\n", forceX);
    fprintf(fpresult, "kappa            %lf\n", kappa);
    fprintf(fpresult, "density          %lf\n", density);
    fprintf(fpresult, "rCut             %lf\n", rCut);
    fprintf(fpresult, "deltaT		%lf\n", deltaT);
    fprintf(fpresult, "stepEquil        %d\n",  stepEquil);
    fprintf(fpresult, "stepLimit        %d\n",  stepLimit);
    fprintf(fpresult, "region[1]        %lf\n", region[1]);
    fprintf(fpresult, "region[2]        %lf\n", region[2]);
    fprintf(fpresult, "cells[1]         %d\n",  cells[1]);
    fprintf(fpresult, "cells[2]         %d\n",  cells[2]);
    fprintf(fpresult, "solver           %s\n",  solver);
    fprintf(fpresult, "boundary         %s %s\n", xBoundary, yBoundary);
    fprintf(fpresult, "------------------------------------\n");
    fprintf(fpresult, "#timeNow Momentum PotEngy KinEngy TotEngy uSumPairPerAtom BondEnergyPerAtom  sPress VirialSum\n");
    fprintf(fpstress, "strain           %lf\n", strain);
    fprintf(fpstress, "region[1]        %lf\n", region[1]);
    fprintf(fpstress, "region[2]        %lf\n", region[2]);
    fprintf(fpstress, "#timeNow virSumxx virSumyy virSumxy pressure\n");
    fprintf(fpmomentum, "#timeNow Px Py\n");
    fprintf(fpvrms, "#timeNow\tVrms \n");
    fprintf(fpcom, "#timeNow\tComX\tComY\n");

   if((strcmp(xBoundary, "p") != 0 && strcmp(xBoundary, "r") != 0) ||
    (strcmp(yBoundary, "p") != 0 && strcmp(yBoundary, "r") != 0)) {
    fprintf(fpresult, "Error: Invalid boundary value detected: '%s %s'. Only 'p' or 'r' are allowed.\n", xBoundary, yBoundary);
    exit(EXIT_FAILURE); // Exit with failure status
  }

}

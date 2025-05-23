#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
typedef double real;

#define	NDIM 2
#define Sqr(x) ((x) * (x))
#define SignR(x, y) (((y) >= 0) ? (x) : (- (x)))

double	*rx, *ry, *vx, *vy, *ax, *ay;
double	*speed;

double region[NDIM+1], regionH[NDIM+1], deltaT, timeNow, potEnergy, kinEnergy, totEnergy, density, 
pressure, rCut, kappa, uSum, virSum, svirSum, vSum, vSumX, vSumY, vvSum, sPotEnergy, sKinEnergy, 
sTotEnergy, sPressure, ssPotEnergy, ssKinEnergy, ssTotEnergy, ssPressure;

int initUcell[NDIM+1], moreCycles, nAtom, stepAvg, stepCount, stepEquil, stepLimit, stepTraj, stepDump;


double RadiusIJ, SqrRadiusIJ, RadiusIJInv; 
int    nAtomType;
int    *atomType;
int    *atomID;
double *atomRadius; 
double *atomMass, TotalMass;

int    nBond, nBondType; 
int	 *atom1, *atom2; 
int	 *BondID, *BondType ;
double *kb, *ro; 
double *BondEnergy, *BondLength;
double TotalBondEnergy, BondEnergyPerAtom;
double gamman;
double *discDragx, *discDragy, *nodeDragx, *nodeDragy;

double strain, strainRate;
double shearDisplacement, shearVelocity;
double VSqr, VMeanSqr, VRootMeanSqr;
double ComX, ComY, ComX0, ComY0, ComXRatio, ComYRatio;
double HaltCondition;
double DeltaY, DeltaX;
int    *ImageX, *ImageY;
double *rxUnwrap, *ryUnwrap;
int    nAtomInterface,  nDiscInterface, nAtomBlock;
int    *atomIDInterface;
double Kn;
double fx, fy, FyBylx, fxByfy;
int    DampFlag;
double strech;

//For dumping the pair interaction data
int    dumpPairFlag;
int    nPairTotal, nPairActive;		
int    *PairID, *Pairatom1, *Pairatom2;
double *PairXij, *PairYij;
 
char   solver[128];
char   xBoundary[10], yBoundary[10];
 
//For damping as in PRL, 130, 178203 (2023)
double *DeltaXijOld, *DeltaYijOld;
double DeltaXijNew, DeltaYijNew;
double DeltaXij, DeltaYij, DeltaVXij, DeltaVYij; 
double **DeltaXijOldPair, **DeltaYijOldPair;

//For molecule-ID as per LAMMPS, helpful!
int    *molID;
int	**isBonded;

//Following three for MPI only
int	 *cellList, cells[NDIM+1];
int 	 rank, size, master;
double *fax, *fay, fuSum, fvirSum, frfAtom;


double uSumPair, uSumPairPerAtom, virSumPair, virSumPairxx, virSumPairyy, virSumPairxy;
double virSumBond, virSumBondxx, virSumBondyy, virSumBondxy;
double virSumxx, virSumyy, virSumxy;
int    freezeAtomType;

// Spacetime Correlations
double **cfOrg, **spacetimeCorr, *cfVal, *spacetimeCorrAv;
int    *indexCorr, countCorrAv, limitCorrAv, nBuffCorr, nFunCorr, nValCorr, stepCorr;

// Viscosity
double rfAtom, frfAtom;
double *indexAcf, **viscAcf, *viscAcfOrg, *viscAcfAv, viscAcfInt;
int    nValAcf, nBuffAcf, stepAcf, countAcfAv, limitAcfAv;

// Radial distribution function
double *histRdf, rangeRdf;
int	 countRdf, limitRdf, sizeHistRdf, stepRdf;


// Output files prefixes
char   *prefix;

char   result[250];
FILE   *fpresult;

char 	xyz[256];
FILE 	*fpxyz;

char 	bond[256];
FILE 	*fpbond;

char 	dump[256];
FILE 	*fpdump;

char 	dnsty[256];
FILE 	*fpdnsty;

char  visc[256];
FILE 	*fpvisc;

char  rdf[256];
FILE  *fprdf;

char  vrms[256];
FILE  *fpvrms;

char  stress[256];
FILE  *fpstress;

char  momentum[256];
FILE  *fpmomentum;

char  com[256];
FILE  *fpcom;

char  pair[256];
FILE  *fppair;

#endif // GLOBAL_H


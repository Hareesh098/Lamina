#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdio.h>  // Required for FILE*

#ifdef DEFINE_GLOBALS
    #define EXTERN
#else
    #define EXTERN extern
#endif

typedef double real;

#define	NDIM 2
#define Sqr(x) ((x) * (x))
#define SignR(x, y) (((y) >= 0) ? (x) : (- (x)))

EXTERN double	*rx, *ry, *vx, *vy, *ax, *ay;
EXTERN double	*speed;

EXTERN double	region[NDIM+1], regionH[NDIM+1], deltaT, timeNow, potEnergy, kinEnergy, totEnergy, 
density, pressure, rCut, kappa, uSum, virSum, svirSum, vSum, vSumX, vSumY, vvSum, sPotEnergy, sKinEnergy, 
sTotEnergy, sPressure, ssPotEnergy, ssKinEnergy, ssTotEnergy, ssPressure;

EXTERN int     initUcell[NDIM+1], moreCycles, nAtom, stepAvg, stepCount, stepEquil, stepLimit, stepTraj, stepDump;

EXTERN double  RadiusIJ, SqrRadiusIJ, RadiusIJInv; 
EXTERN int     nAtomType;
EXTERN int     *atomType;
EXTERN int     *atomID;
EXTERN double  *atomRadius; 
EXTERN double  *atomMass, TotalMass; 

EXTERN int     nBond, nBondType; 
EXTERN int     *atom1, *atom2; 
EXTERN int     *BondID, *BondType ;
EXTERN double  *kb, *ro; 
EXTERN double  *BondEnergy, *BondLength;
EXTERN double  TotalBondEnergy, BondEnergyPerAtom;
EXTERN double  gamman;
EXTERN double  *discDragx, *discDragy, *nodeDragx, *nodeDragy;
EXTERN double  strain, strainRate;
EXTERN double  shearDisplacement, shearVelocity;
EXTERN double  VSqr, VMeanSqr, VRootMeanSqr;
EXTERN double  ComX, ComY, ComX0, ComY0, ComXRatio, ComYRatio;
EXTERN double  HaltCondition;
EXTERN double  DeltaY, DeltaX;
EXTERN int     *ImageX, *ImageY;
EXTERN double  *rxUnwrap, *ryUnwrap;
EXTERN int     nAtomInterface, nDiscInterface,  nAtomBlock;
EXTERN int     *atomIDInterface;
EXTERN double  Kn;
EXTERN double  fx, fy, FyBylx, fxByfy;
EXTERN int     DampFlag;
EXTERN double  strech;

//For dumping the pair interaction data
EXTERN int     dumpPairFlag;
EXTERN int     nPairTotal, nPairActive;
EXTERN int     *PairID, *Pairatom1, *Pairatom2;
EXTERN double  *PairXij, *PairYij;


EXTERN char	solver[128];
EXTERN char	xBoundary[10], yBoundary[10];
EXTERN char     thermo;

//For damping as in PRL, 130, 178203 (2023)
EXTERN double *DeltaXijOld, *DeltaYijOld;
EXTERN double DeltaXijNew, DeltaYijNew;
EXTERN double DeltaXij, DeltaYij, DeltaVXij, DeltaVYij; 
EXTERN double **DeltaXijOldPair, **DeltaYijOldPair;

//For molecule-ID as per LAMMPS, helpful!
EXTERN int    *molID;
EXTERN int    **isBonded;

//Following three for MPI only
EXTERN int     *cellList, cells[NDIM+1];
EXTERN int     rank, size, master;
EXTERN double  *fax, *fay, fuSum, fvirSum, frfAtom;

//For thermodynamic properties 
EXTERN double  uSumPair, uSumPairPerAtom, virSumPair, virSumPairxx, virSumPairyy, virSumPairxy;
EXTERN double  virSumBond, virSumBondxx, virSumBondyy, virSumBondxy;
EXTERN double  virSumxx, virSumyy, virSumxy;
EXTERN int     freezeAtomType;

// Spacetime Correlations
EXTERN double  **cfOrg, **spacetimeCorr, *cfVal, *spacetimeCorrAv;
EXTERN int     *indexCorr, countCorrAv, limitCorrAv, nBuffCorr, nFunCorr, nValCorr, stepCorr;

// Viscosity
EXTERN double  rfAtom, frfAtom;
EXTERN double  *indexAcf, **viscAcf, *viscAcfOrg, *viscAcfAv, viscAcfInt;
EXTERN int      nValAcf, nBuffAcf, stepAcf, countAcfAv, limitAcfAv;

// Radial distribution function
EXTERN double  *histRdf, rangeRdf;
EXTERN int     countRdf, limitRdf, sizeHistRdf, stepRdf;


// Output files prefixes
EXTERN char	   *prefix;

EXTERN char    result[250];
EXTERN FILE    *fpresult;

EXTERN char    xyz[256];
EXTERN FILE    *fpxyz;

EXTERN char    bond[256];
EXTERN FILE    *fpbond;


EXTERN char    dump[256];
EXTERN FILE    *fpdump;

EXTERN char    dnsty[256];
EXTERN FILE    *fpdnsty;

EXTERN char    visc[256];
EXTERN FILE    *fpvisc;

EXTERN char    rdf[256];
EXTERN FILE    *fprdf;

EXTERN char    vrms[256];
EXTERN FILE    *fpvrms;

EXTERN char    stress[256];
EXTERN FILE    *fpstress;

EXTERN char    momentum[256];
EXTERN FILE    *fpmomentum;

EXTERN char    com[256];
EXTERN FILE    *fpcom;

EXTERN char    pair[256];
EXTERN FILE    *fppair;

#endif // GLOBALEXTERN_H

#ifndef GLOBALEXTERN_H
#define GLOBALEXTERN_H

typedef double real;

#define	NDIM 2
#define Sqr(x) ((x) * (x))
#define SignR(x, y) (((y) >= 0) ? (x) : (- (x)))

extern double	*rx, *ry, *vx, *vy, *ax, *ay;
extern double	*speed;

extern double	region[NDIM+1], regionH[NDIM+1], deltaT, timeNow, potEnergy, kinEnergy, totEnergy, 
density, pressure, rCut, kappa, uSum, virSum, svirSum, vSum, vSumX, vSumY, vvSum, sPotEnergy, sKinEnergy, 
sTotEnergy, sPressure, ssPotEnergy, ssKinEnergy, ssTotEnergy, ssPressure;

extern int     initUcell[NDIM+1], moreCycles, nAtom, stepAvg, stepCount, stepEquil, stepLimit, stepTraj, stepDump;

extern double  RadiusIJ, SqrRadiusIJ, RadiusIJInv; 
extern int     nAtomType;
extern int     *atomType;
extern int     *atomID;
extern double  *atomRadius; 
extern double  *atomMass, TotalMass; 

extern int     nBond, nBondType; 
extern int     *atom1, *atom2; 
extern int     *BondID, *BondType ;
extern double  *kb, *ro; 
extern double  *BondEnergy, *BondLength;
extern double  TotalBondEnergy, BondEnergyPerAtom;
extern double  gamman;
extern double  *discDragx, *discDragy, *nodeDragx, *nodeDragy;
extern double  strain, strainRate;
extern double  shearDisplacement, shearVelocity;
extern double  VSqr, VMeanSqr, VRootMeanSqr;
extern double  ComX, ComY, ComX0, ComY0, ComXRatio, ComYRatio;
extern double  HaltCondition;
extern double  DeltaY, DeltaX;
extern int     *ImageX, *ImageY;
extern double  *rxUnwrap, *ryUnwrap;
extern int     nAtomInterface, nDiscInterface,  nAtomBlock;
extern int     *atomIDInterface;
extern double  Kn;
extern double  fx, fy, FyBylx, fxByfy;
extern int     DampFlag;
extern double  strech;

//For dumping the pair interaction data
extern int     dumpPairFlag;
extern int     nPairTotal, nPairActive;
extern int     *PairID, *Pairatom1, *Pairatom2;
extern double  *PairXij, *PairYij;


extern char	solver[128];
extern char	xBoundary[10], yBoundary[10];

//For damping as in PRL, 130, 178203 (2023)
extern double *DeltaXijOld, *DeltaYijOld;
extern double DeltaXijNew, DeltaYijNew;
extern double DeltaXij, DeltaYij, DeltaVXij, DeltaVYij; 
extern double **DeltaXijOldPair, **DeltaYijOldPair;

//For molecule-ID as per LAMMPS, helpful!
extern int    *molID;
extern int    **isBonded;

//Following three for MPI only
extern int     *cellList, cells[NDIM+1];
extern int     rank, size, master;
extern double  *fax, *fay, fuSum, fvirSum, frfAtom;

//For thermodynamic properties 
extern double  uSumPair, uSumPairPerAtom, virSumPair, virSumPairxx, virSumPairyy, virSumPairxy;
extern double  virSumBond, virSumBondxx, virSumBondyy, virSumBondxy;
extern double  virSumxx, virSumyy, virSumxy;
extern int     freezeAtomType;

// Spacetime Correlations
extern double  **cfOrg, **spacetimeCorr, *cfVal, *spacetimeCorrAv;
extern int     *indexCorr, countCorrAv, limitCorrAv, nBuffCorr, nFunCorr, nValCorr, stepCorr;

// Viscosity
extern double  rfAtom, frfAtom;
extern double  *indexAcf, **viscAcf, *viscAcfOrg, *viscAcfAv, viscAcfInt;
extern int      nValAcf, nBuffAcf, stepAcf, countAcfAv, limitAcfAv;

// Radial distribution function
extern double  *histRdf, rangeRdf;
extern int     countRdf, limitRdf, sizeHistRdf, stepRdf;


// Output files prefixes
extern char	   *prefix;

extern char    result[250];
extern FILE    *fpresult;

extern char    xyz[256];
extern FILE    *fpxyz;

extern char    bond[256];
extern FILE    *fpbond;


extern char    dump[256];
extern FILE    *fpdump;

extern char    dnsty[256];
extern FILE    *fpdnsty;

extern char    visc[256];
extern FILE    *fpvisc;

extern char    rdf[256];
extern FILE    *fprdf;

extern char    vrms[256];
extern FILE    *fpvrms;

extern char    stress[256];
extern FILE    *fpstress;

extern char    momentum[256];
extern FILE    *fpmomentum;

extern char    com[256];
extern FILE    *fpcom;

extern char    pair[256];
extern FILE    *fppair;

#endif // GLOBALEXTERN_H

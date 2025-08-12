#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
#include <time.h> 
//#include <mpi.h> //For future parallel version
#define DEFINE_GLOBALS
#include "global.h"
#include "ComputeBondForce.h"
#include "ComputePairForce.h"


char *prefix = NULL;  // Definition of prefix
void Init();
void SetupJob();
void EvalSpacetimeCorr();
void Trajectory();
void DumpState();
void ComputeForcesCells();
void ApplyBoundaryCond();
void EvalProps();
void AccumProps(int icode);
void PrintSummary();
void PrintVrms();
void VelocityVerletStep(int icode);
void ApplyForce();
void ApplyLeesEdwardsBoundaryCond();
void PrintStress();
void Close();
void PrintMomentum();
void DisplaceAtoms();
void DumpRestart(); 
bool HaltConditionCheck(double value); 
void EvalCom();
void PrintCom();
void EvalVrms();
void EvalUnwrap();
void DumpBonds();
void DumpPairs();
void WriteBinaryRestart();
void PrintForceSum();

int main(int argc, char **argv) {
 time_t t1 = 0, t2;
 if (argc < 2) {
 fprintf(stderr, "Usage: %s <output_prefix>\n", argv[0]);
 return 1;
 }

 int prefix_size = snprintf(NULL, 0, "../output/%s", argv[1]) + 1; // +1 for the null terminator
 prefix = malloc(prefix_size);
 if(prefix == NULL) {
  fprintf(stderr, "Memory allocation failed\n");
 return 1;
 }

   // Write the formatted string into the allocated space
  snprintf(prefix, prefix_size, "../output/%s", argv[1]);
  sprintf(result, "%s.result", prefix);
  fpresult = fopen(result, "w");
  sprintf(xyz, "%s.xyz", prefix);
  fpxyz = fopen(xyz, "w");
  sprintf(vrms, "%s.vrms", prefix);
  fpvrms = fopen(vrms, "w");
  sprintf(bond, "%s.bond", prefix);
  fpbond = fopen(bond, "w");
  sprintf(com, "%s.com", prefix);
  fpcom = fopen(com, "w");
  sprintf(pair, "%s.pair", prefix);
  fppair = fopen(pair, "w");
  sprintf(force, "%s.force", prefix);
  fpforce = fopen(force, "w");
  
  /* //Uncomment the following as per your acquirement 
  sprintf(dnsty, "%s.curr-dnsty", prefix);
  fpdnsty = fopen(dnsty, "w");
  sprintf(visc, "%s.viscosity", prefix);
  fpvisc = fopen(visc, "w");
  sprintf(rdf, "%s.rdf", prefix);
  fprdf = fopen(rdf, "w");
  sprintf(stress, "%s.stress", prefix);
  fpstress = fopen(stress, "w");
  sprintf(momentum, "%s.momentum", prefix);
  fpmomentum = fopen(momentum, "w");
  */  
 
  Init();
  SetupJob();
  t1 = time(NULL);
  moreCycles = 1;
  if(stepCount >= 0) {
   if (timeNow == 0.0) {
    printf(">>> Run type: Fresh simulation <<<\n");
    DisplaceAtoms();
    ComputePairForce(1);
    ComputeBondForce();
    ApplyForce();
    } else {
    printf(">>> Run type: Restart simulation <<<\n");
   }
   DumpBonds();
   DumpPairs();
   Trajectory();
   EvalUnwrap();
   ApplyBoundaryCond();
   EvalProps();
   EvalVrms();
   EvalCom();
   PrintVrms();
   PrintCom();
   PrintSummary();
   PrintForceSum();
   }

//Here starts the main loop of the program 
  while(moreCycles){
   if(stepLimit == 0){
   printf("Error occured: stepLimit must be > 0\n");
   printf("Exiting now ...\n");
   exit(0);
   }

   stepCount ++;
   timeNow += deltaT ; //stepCount * deltaT; //for adaptive step size: timeNow += deltaT

   VelocityVerletStep(1);
   EvalUnwrap();
   ApplyBoundaryCond();
   ComputePairForce(1);
   ComputeBondForce();
   ApplyForce();
   VelocityVerletStep(2);
   ApplyBoundaryCond();
   EvalProps();
   EvalVrms();
   EvalCom();
   if(stepCount % stepAvg == 0){
    PrintSummary();
    PrintVrms();
    PrintCom();
    PrintForceSum();
    }
   if(stepCount % stepTraj == 0){
    Trajectory();
    DumpBonds();
    DumpPairs();
    }
   if(stepCount % stepDump == 0){
    DumpRestart();     // Save the current state for input
    DumpState();       // Save the current state for config
    WriteBinaryRestart();
   }
   if(HaltConditionCheck(VRootMeanSqr)) {
    DumpRestart();     // Save the current state for input
    DumpState();       // Save the current state for config
    WriteBinaryRestart();
    break;  // Exit the loop when the halt condition is met
    }
    
    moreCycles ++;
    if(moreCycles >= stepLimit)
    moreCycles = 0;
  }


  t2 = time(NULL);
  fprintf(fpresult, "#Execution time %lf secs\n", difftime(t2,t1));
  fprintf(fpresult, "#Execution speed %lf steps per secs\n", stepLimit/difftime(t2,t1));
  printf(">>> Simulation run completed <<<\n");
  printf(">>> Execution time %lf secs <<<\n", difftime(t2,t1));
  printf(">>> Execution speed %lf steps per secs <<< \n", stepLimit/difftime(t2,t1));

  fclose(fpresult);
  fclose(fpxyz);
  fclose(fpvrms);
  fclose(fpbond);
  fclose(fppair);
  fclose(fpcom);
  fclose(fpforce);

/*//Uncomment the following as per your acquirement    
  fclose(fpdnsty);
  fclose(fpvisc);
  fclose(fprdf);
  fclose(fpstress);
  fclose(fpmomentum);
*/

  free(prefix);
  Close();
  return 0;
} 

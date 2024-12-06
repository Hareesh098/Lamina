#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h> 
#include"global.h"
#include"globalExtern.h"
char *prefix = NULL;  // Definition of prefix

void Init();
void SetupJob();
void EvalSpacetimeCorr();
void Trajectory();
void DumpState();
void ComputeForcesCells();
void LeapfrogStep();
void BrownianStep();
void ApplyBoundaryCond();
void EvalProps();
void EvalVacf();
void EvalRdf();
void AccumProps(int icode);
void PrintSummary();
void PrintVrms();
void ComputeBondForce();
void DumpBonds();
void VelocityVerletStep(int icode);
void ApplyForce();
void ApplyDrivingForce();
void ApplyShear();
void ApplyLeesEdwardsBoundaryCond();
void PrintStress();
void Close();
void ComputePairForce();
void PrintMomentum();

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
  sprintf(dump, "%s.STATE", prefix);
  fpdump = fopen(dump, "w");
  sprintf(dnsty, "%s.curr-dnsty", prefix);
  fpdnsty = fopen(dnsty, "w");
  sprintf(visc, "%s.viscosity", prefix);
  fpvisc = fopen(visc, "w");
  sprintf(rdf, "%s.rdf", prefix);
  fprdf = fopen(rdf, "w");
  sprintf(vrms, "%s.vrms", prefix);
  fpvrms = fopen(vrms, "w");
  sprintf(bond, "%s.bond", prefix);
  fpbond = fopen(bond, "w");
  sprintf(stress, "%s.stress", prefix);
  fpstress = fopen(stress, "w");
  sprintf(momentum, "%s.momentum", prefix);
  fpmomentum = fopen(momentum, "w");


  Init();
  SetupJob();
  t1 = time(NULL);
  moreCycles = 1;
  timeNow = 0.0;
  if(timeNow == 0.0) {
   Trajectory();  
   ApplyBoundaryCond();
   }

//Here starts the main loop of the program 
  while(moreCycles){
   stepCount ++;
   timeNow += deltaT;


   ComputePairForce();
   ComputeBondForce();
   VelocityVerletStep(1);
   ApplyBoundaryCond();
   //ApplyForce();
   //ApplyDrivingForce();
   ComputePairForce();
   ComputeBondForce();
   VelocityVerletStep(2);
   ApplyBoundaryCond();
   EvalProps();
   AccumProps(1);
   if(stepCount % stepAvg == 0){
    AccumProps(2);
    PrintSummary();
    PrintStress();
    AccumProps(0);
    PrintMomentum();
    }
   if(stepCount % stepTraj == 0){
    Trajectory();
    DumpBonds();
    }
    if(stepCount % stepDump == 0)
    DumpState();
    if(stepCount >= stepLimit)
     moreCycles = 0;
  }


  t2 = time(NULL);
  fprintf(fpresult, "#Execution time %lf secs\n", difftime(t2,t1));

  fclose(fpresult);
  fclose(fpxyz);
  fclose(fpvrms);
  fclose(fpdnsty);
  fclose(fpvisc);
  fclose(fprdf);
  fclose(fpbond);
  fclose(fpstress);
  fclose(fpmomentum);
  free(prefix);
  Close();
  return 0;
} 

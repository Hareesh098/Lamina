#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "globalExtern.h" //Definitions of global variables
void HaltConditionCheck(double value, int stepCount){
double HaltCondition;
HaltCondition = 1e-6;
 if(value <= HaltCondition && value != 0){
 fprintf(fpresult, "Halt condition met at step = %d with Vrms = %.10f\n", stepCount, value);
 fclose(fpresult);  // Close the results file
 exit(0);           // Terminate the program
 } }

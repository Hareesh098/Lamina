#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "globalExtern.h" // Definitions of global variables
bool HaltConditionCheck(double value, int stepCount) {
  
  if(value <= HaltCondition && value != 0) {
  fprintf(fpresult, "Halt condition met at step = %d with Vrms = %.10f\n", stepCount, value);
  return true;       // Signal that the halt condition is met
  }
 return false; // Halt condition not met
}


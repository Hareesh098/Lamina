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
#include <stdbool.h>
#include "global.h" 

bool HaltConditionCheck(double value, int stepCount) {
  
  if(value <= HaltCondition && value != 0) {
  fprintf(fpresult, "Halt condition met at step = %d with Vrms = %.10f\n", stepCount, value);
  return true;       // Signal that the halt condition is met
  }
 return false; // Halt condition not met
}


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
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"global.h"

void ApplyBoundaryCond(){
  int n;
  for(n = 1 ; n <= nAtom ; n ++){
   if(strcmp(xBoundary, "p") == 0 && strcmp(yBoundary, "p") == 0){         // P.B.C along x and y axis
    rx[n] -= region[1]*rint(rx[n]/region[1]);
    ry[n] -= region[2]*rint(ry[n]/region[2]);
   } else if (strcmp(xBoundary, "r") == 0 && strcmp(yBoundary, "r") == 0){   //R.B.C. along x and y axis
     if((rx[n] + atomRadius[n]) >= regionH[1]){
        rx[n] = 0.999999*regionH[1] - atomRadius[n]; vx[n] = -vx[n] ;
     }if((rx[n]-atomRadius[n]) < -regionH[1]){
        rx[n] = -0.999999*regionH[1] + atomRadius[n]; vx[n] = -vx[n] ;
    }
     if((ry[n] + atomRadius[n])>= regionH[2]){
        ry[n] = 0.999999*regionH[2] - atomRadius[n]; vy[n] = -vy[n] ;
     }if((ry[n]-atomRadius[n]) < -regionH[2]){
        ry[n] = -0.999999*regionH[2] + atomRadius[n]; vy[n] = -vy[n] ;
    }} 
    else if (strcmp(xBoundary, "p") == 0 && strcmp(yBoundary, "r") == 0){   //P.B.C. along x and R.B.C along y axis
    rx[n] -= region[1]*rint(rx[n]/region[1]); 
    if((ry[n] + atomRadius[n]) >= regionH[2]){
      ry[n] = 0.999999*regionH[2] - atomRadius[n]; vy[n] = -vy[n] ;
     }if((ry[n] - atomRadius[n]) < -regionH[2]){
        ry[n] = -0.999999*regionH[2] + atomRadius[n]; vy[n] = -vy[n] ;
  }} 
    else if(strcmp(xBoundary, "r") == 0 && strcmp(yBoundary, "p") == 0){   //R.B.C. along x and P.B.C along y axis
    if((rx[n] + atomRadius[n]) >= regionH[1]){
       rx[n] = 0.999999*regionH[1] - atomRadius[n]; vx[n] = -vx[n] ;
     }if((rx[n] - atomRadius[n]) < -regionH[1]){
      rx[n] = -0.999999*regionH[1] + atomRadius[n]; vx[n] = -vx[n] ;
     } 
     ry[n] -= region[2]*rint(ry[n]/region[2]);  
  } else {
    // Print error message and exit the program
    fprintf(fpresult, "Error: Invalid boundary configuration: '%s %s'\n", xBoundary, yBoundary);
    exit(EXIT_FAILURE); // Exit with failure status 
  }
 }
}

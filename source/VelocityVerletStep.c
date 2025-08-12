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
#include<math.h>
#include"global.h"

void VelocityVerletStep(int icode){
int n;
double atomMassi;
   
 if(icode == 1){
 for (n= 1; n <= nAtom; n++) {
  if(atomType[n] != freezeAtomType){
  atomMassi = 1./atomMass[n];
  ax[n] = fx[n] * atomMassi;    ay[n] = fy[n] * atomMassi;    
  vx[n] += ax[n] * 0.5 * deltaT; 
  vy[n] += ay[n] * 0.5 * deltaT;
  rx[n] += vx[n] * deltaT; 
  ry[n] += vy[n] * deltaT;
  } 
  //Calculating the image flags here
  if (rx[n] >= regionH[1]) {
   rx[n] -= region[1];
   ImageX[n]++;
   } else if (rx[n] < -regionH[1]) {
   rx[n] += region[1];
  ImageX[n]--;
  }
  if (ry[n] >= regionH[2]) {
   ry[n] -= region[2];
   ImageY[n]++;
   } else if (ry[n] < -regionH[2]) {
   ry[n] += region[2];
   ImageY[n]--;
   } } }
  else if(icode == 2){
  for(n = 1; n <= nAtom; n++) {
  if(atomType[n] != freezeAtomType){
   atomMassi = 1./atomMass[n];
   ax[n] = fx[n] * atomMassi;    ay[n] = fy[n] * atomMassi;    
   vx[n] += ax[n] * 0.5 * deltaT; 
   vy[n] += ay[n] * 0.5 * deltaT;
} } } }


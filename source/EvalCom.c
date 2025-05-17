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
#include<math.h>
#include"global.h"

void EvalCom(){
 int n;
 ComX = 0.0; ComY = 0.0; ComXRatio = 0.0; ComYRatio = 0.0;
 TotalMass = 0.0;
  
 for(n=1; n<=nAtom; n++){
 if(molID[n] == 2){
  ComX += atomMass[n] * rxUnwrap[n]; 
  ComY += atomMass[n] * ryUnwrap[n]; 
  TotalMass += atomMass[n];
  } }

  ComX = ComX/TotalMass;
  ComY = ComY/TotalMass;

  if(timeNow == 0.0){
  ComX0 = ComX; ComY0 = ComY;
  }
  ComXRatio = ComX/ComX0;   ComYRatio = ComY/ComY0;
 }
  
  
  

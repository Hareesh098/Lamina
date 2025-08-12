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

void PrintForceSum(){
 int n;
 double forceSumxAtomType1, forceSumxAtomType2, forceSumxAtomType3, forceSumxAtomType4, forceSumxAtomType5;
 double forceSumyAtomType1, forceSumyAtomType2, forceSumyAtomType3, forceSumyAtomType4, forceSumyAtomType5;
 
 forceSumxAtomType1 = 0.0;  forceSumyAtomType1 = 0.0; 
 forceSumxAtomType2 = 0.0;  forceSumyAtomType2 = 0.0; 
 forceSumxAtomType3 = 0.0;  forceSumyAtomType3 = 0.0; 
 forceSumxAtomType4 = 0.0;  forceSumyAtomType4 = 0.0; 
 forceSumxAtomType5 = 0.0;  forceSumyAtomType5 = 0.0; 


 for(n = 1; n <= nAtom; n++){
 if(atomType[n] == 1){
  forceSumxAtomType1 += fx[n];
  forceSumyAtomType1  += fy[n];
  } else if(atomType[n] == 2){
  forceSumxAtomType2 += fx[n];
  forceSumyAtomType2  += fy[n];
  } else if(atomType[n] == 3){
  forceSumxAtomType3 += fx[n];
  forceSumyAtomType3  += fy[n];
  } else if(atomType[n] == 4){
  forceSumxAtomType4 += fx[n];
  forceSumyAtomType4 += fy[n];
  } else if(atomType[n] == 5){
  forceSumxAtomType5 += fx[n];
  forceSumyAtomType5 += fy[n];
  }
 } 

 fprintf(fpforce, "%0.4lf\t%0.16lf\t%0.16lf\t%0.16lf\t%0.16lf\t%0.16f\t%0.16lf\t%0.16lf\t%0.16lf\t%0.16lf\t%0.16lf\t%0.16f\t%0.16f\n", timeNow, 
 forceSumxAtomType1, forceSumyAtomType1, 
 forceSumxAtomType2, forceSumyAtomType2, 
 forceSumxAtomType3, forceSumyAtomType3, 
 forceSumxAtomType4, forceSumyAtomType4, 
 forceSumxAtomType5, forceSumyAtomType5, 
 forceSumxExtern, forceSumyExtern);
 fflush(fpforce);
 }
  
  
  

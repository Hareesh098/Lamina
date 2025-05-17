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
#include"global.h"

double Integrate(double *, int);
 void PrintVacf();
 void ZeroVacf();
 void AccumVacf(){
 double fac;
 int j, nb;
 for(nb = 1 ; nb <= nBuffAcf ; nb ++){
  if(indexAcf[nb] == nValAcf){
   for(j = 1 ; j <= nValAcf; j ++){
    viscAcfAv[j] +=  viscAcf[nb][j];
    }
  indexAcf[nb] = 0;
  countAcfAv ++;
  if(countAcfAv == limitAcfAv){
   fac = 1./(kinEnergy*region[1]*region[2]*limitAcfAv);
   viscAcfInt = fac*stepAcf*deltaT*Integrate(viscAcfAv, nValAcf);
   PrintVacf();
   ZeroVacf();
} } } }


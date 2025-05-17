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
#include"globalExtern.h"
void AccumProps(int icode){
  if(icode == 0){
    sPotEnergy = ssPotEnergy = 0.;
    sKinEnergy = ssKinEnergy = 0.;
    sPressure = ssPressure = 0.;
    sTotEnergy = ssTotEnergy = 0.; 
    svirSum = 0.;
  }else if(icode == 1){
    sPotEnergy += potEnergy;
    ssPotEnergy += Sqr(potEnergy);
    sKinEnergy += kinEnergy;
    ssKinEnergy += Sqr(kinEnergy);
    sTotEnergy += totEnergy;
    ssTotEnergy += Sqr(totEnergy);
    sPressure += pressure;
    ssPressure += Sqr(pressure);
    svirSum += virSum;
  }else if(icode == 2){
    sPotEnergy /= stepAvg;
    ssPotEnergy /= sqrt(ssPotEnergy/stepAvg - Sqr(sPotEnergy));
    sTotEnergy /= stepAvg;
    ssTotEnergy = sqrt(ssTotEnergy/stepAvg - Sqr(sTotEnergy));
    sKinEnergy /= stepAvg;
    ssKinEnergy = sqrt(ssKinEnergy/stepAvg - Sqr(sKinEnergy));
    sPressure /= stepAvg;
    ssPressure = sqrt(ssPressure/stepAvg - Sqr(sPressure));
    svirSum /= stepAvg;
  }
}

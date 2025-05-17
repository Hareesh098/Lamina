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

void ComputeForcesCells(){
  double dr[NDIM+1], invWid[NDIM+1], shift[NDIM+1], f, fcVal, rr, ri, r, uVal;
  int c, I, J, m1, m1X, m1Y, m2, m2X, m2Y, n, offset;
  int iofX[] = {0, 0, 1, 1, 0, -1, -1, -1, 0, 1},
      iofY[] = {0, 0, 0, 1 ,1, 1, 0, -1, -1, -1};

  invWid[1] = cells[1]/region[1];
  invWid[2] = cells[2]/region[2];

  for(n = nAtom+1; n <= nAtom+cells[1]*cells[2] ; n++)
    cellList[n] = 0;
  
  for(n = 1 ; n <= nAtom ; n ++){
    c = ((int)((ry[n] + regionH[2])*invWid[2]))*cells[1] + (int)((rx[n]+regionH[1])*invWid[1]) + nAtom+ 1;
    cellList[n] = cellList[c];
    cellList[c] = n;
  }
  
  for(n = 1 ; n <= nAtom ; n ++){
    ax[n] = 0.;
    ay[n] = 0.;
  }
  
  uSum = 0.0 ;
  virSum = 0.0;
  rfAtom = 0.0;
  RadiusIJ = 0.0;

  gamman = 1.0;
  double vr[NDIM+1], fd, fdVal, rrinv;
  rrinv = 0.0;
  fd = 0.0;
  fdVal = 0.0; 
  
  int start = 1 + rank*(cells[2]/size);
  int end = (rank+1)*(cells[2]/size);

  for(m1Y = start ; m1Y <= end ; m1Y ++){
    for(m1X = 1 ; m1X <= cells[1] ; m1X ++){
      m1 = (m1Y-1) * cells[1] + m1X + nAtom;
      for(offset = 1 ; offset <= 9 ; offset ++){
	m2X = m1X + iofX[offset]; shift[1] = 0.;
	if(m2X > cells[1]){
	  m2X = 1; shift[1] = region[1];
	}else if(m2X == 0){
	  m2X = cells[1]; shift[1] = -region[1];
	}
	m2Y = m1Y + iofY[offset]; shift[2] = 0.;
	if(m2Y > cells[2]){
	  m2Y = 1; shift[2] = region[2];
	}else if(m2Y == 0){
	  m2Y = cells[2]; shift[2] = -region[2];
	}
	m2 = (m2Y-1)*cells[1] + m2X + nAtom;
	I = cellList[m1];
	while(I > 0){
	  J = cellList[m2];
	  while(J > 0){
	    if(m1 == m2 && J != I && (atomRadius[I] > 0. && atomRadius[J] > 0.)){
	      dr[1] = rx[I] - rx[J] - shift[1];
	      dr[2] = ry[I] - ry[J] - shift[2];
	      rr = Sqr(dr[1]) + Sqr(dr[2]);
	      RadiusIJ = atomRadius[I] + atomRadius[J];
	      SqrRadiusIJ = Sqr(RadiusIJ);
	      if(rr < SqrRadiusIJ){
		r = sqrt(rr);
		ri = 1.0/r;
                rrinv = 1.0/rr;
                vr[1] = vx[I] - vx[J];
                vr[2] = vy[I] - vy[J];
		RadiusIJInv = 1.0/RadiusIJ;
		uVal = Sqr(1.0 - r * RadiusIJInv);
		fcVal = 2.0 * RadiusIJInv * (1.0 - r * RadiusIJInv) *ri;
                fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rrinv; //disc-disc drag

		f  = fcVal * dr[1];
                fd = fdVal * dr[1];
		ax[I] += (f + fd);
                discDragx[I] += fd; //disc-disc drag

		f = fcVal * dr[2];
                fd = fdVal * dr[2];
		ay[I] += (f + fd);
                discDragy[I] += fd; //disc-disc drag

		uSum +=  0.5 * uVal;
		virSum += 0.5 * fcVal * rr;
		rfAtom += 0.5 * dr[1] * fcVal * dr[2];
	      }
	    }else if(m1 != m2 && (atomRadius[I] > 0. && atomRadius[J] > 0.)){
	      dr[1] = rx[I] - rx[J] - shift[1];
	      dr[2] = ry[I] - ry[J] - shift[2];
	      rr = Sqr(dr[1]) + Sqr(dr[2]);
	      RadiusIJ = atomRadius[I] + atomRadius[J];
	      SqrRadiusIJ = Sqr(RadiusIJ);
	      if(rr < SqrRadiusIJ){
		r = sqrt(rr);
		ri = 1.0/r;
                rrinv = 1.0/r;
                vr[1] = vx[I] - vx[J];
                vr[2] = vy[I] - vy[J];
		RadiusIJInv = 1.0/RadiusIJ;
		uVal = Sqr(1.0 - r * RadiusIJInv);
		fcVal = 2.0 * RadiusIJInv * (1.0 - r * RadiusIJInv) *ri;
                fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rrinv; //disc-disc drag

		f  = fcVal * dr[1];
                fd =  fdVal * dr[1];
		ax[I] += (f + fd);
                discDragx[I] += fd; //disc-disc drag

		f  = fcVal * dr[2];
                fd = fdVal * dr[2];
		ay[I] += (f + fd);
                discDragy[I] += fd; //disc-disc drag

		uSum +=  0.5 * uVal;
		virSum += 0.5 * fcVal * rr;
		rfAtom += 0.5 * dr[1] * fcVal * dr[2];
	      }
	    }
       	    J = cellList[J];
	  }
	  I = cellList[I];
	}
      }
    }
  }
}

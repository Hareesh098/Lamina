#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void ApplyDrivingForce(){
 int n;
 double Vxblock, Vyblock;
 double Vxsubstrate, Vysubstrate;
 Vxblock = 0.0;  Vyblock = 0.0; 
 Vxsubstrate = 0.0; Vysubstrate = 0.0;
 double gammav;
 gammav = 0.0;

 double count_substrate = 0;
 double count_block = 0;

 for(n = 1 ; n <= nAtom; n ++){
  if(atomType[n] == 1 || atomType[n] == 2){
  Vxsubstrate += vx[n]; Vysubstrate += vy[n]; 
  count_substrate++;
  }
  if(atomType[n] == 3 || atomType[n] == 4){
  Vxblock += vx[n]; Vyblock += vy[n]; 
  count_block++;
  } }

  if(count_substrate > 0) {
    Vxsubstrate /= count_substrate;
    Vysubstrate /= count_substrate;
  }

  if(count_block > 0) {
   Vxblock /= count_block;
   Vyblock /= count_block;
  }

 for(n = 1 ; n <= nAtom; n ++){
  if(atomType[n] == 1 || atomType[n] == 2){
  ax[n] += -gammav * (vx[n] - Vxsubstrate);
  ay[n] += -gammav * (vy[n] - Vysubstrate);
  }
  if(atomType[n] == 3 || atomType[n] == 4){
  ax[n] += -gammav * (vx[n] - Vxblock);
  ay[n] += -gammav * (vy[n] - Vyblock);
 } } }



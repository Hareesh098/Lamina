#include<stdio.h>
#include"globalExtern.h"
double Integrate(double *f, int nf){
  double s;
  int i;
  s = 0.5*(f[1] + f[nf]);
  for(i = 2 ; i <= nf - 1 ; i ++)
    s += f[i];
  return(s);
}


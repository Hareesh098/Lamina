#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"globalExtern.h"
void PrintCom(){
  fprintf(fpcom, "%0.4lf\t%0.16lf\t%0.16lf\n", timeNow, ComX, ComY);
  fflush(fpcom);
  
  }
  
  
  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globalExtern.h"

void EvalUnwrap() {
 int n;
 for (n = 1; n <= nAtom; n++) {
  ImageX[n] += (rx[n] >= regionH[1]) - (rx[n] < -regionH[1]);
  ImageY[n] += (ry[n] >= regionH[2]) - (ry[n] < -regionH[2]);
  rxUnwrap[n] = rx[n] + ImageX[n] * region[1];
  ryUnwrap[n] = ry[n] + ImageY[n] * region[2];
  }
}


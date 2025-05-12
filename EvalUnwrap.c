#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globalExtern.h"

void EvalUnwrap() {
 int n;
 for (n = 1; n <= nAtom; n++) {
  rxUnwrap[n] = rx[n] + ImageX[n] * region[1];
  ryUnwrap[n] = ry[n] + ImageY[n] * region[2];
  }
}


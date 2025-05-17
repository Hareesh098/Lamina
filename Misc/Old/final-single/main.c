#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../source/globalExtern.h"
#include "../source/global.h"
#include "../source/ComputeBondForce.h"
#include "TestComputeBondForce.h"
// Test tolerance for floating point comparisons
const double TOL = 1e-6;

// Setup before each test
void setUp(void) {
    nAtom = 2;
    nBond = 1;
    gamman = 0.0;
    DampFlag = 1;

    // Allocate all required global arrays
    rx = calloc(nAtom + 1, sizeof(double));
    ry = calloc(nAtom + 1, sizeof(double));
    vx = calloc(nAtom + 1, sizeof(double));
    vy = calloc(nAtom + 1, sizeof(double));
    ax = calloc(nAtom + 1, sizeof(double));
    ay = calloc(nAtom + 1, sizeof(double));
    nodeDragx = calloc(nAtom + 1, sizeof(double));
    nodeDragy = calloc(nAtom + 1, sizeof(double));
    atom1 = calloc(nBond + 1, sizeof(int));
    atom2 = calloc(nBond + 1, sizeof(int));
    kb = calloc(nBond + 1, sizeof(double));
    ro = calloc(nBond + 1, sizeof(double));
    BondEnergy = calloc(nBond + 1, sizeof(double));
    BondLength = calloc(nBond + 1, sizeof(double));

    // Box setup
    region[1] = region[2] = 100.0;
    regionH[1] = regionH[2] = 50.0;
    shearDisplacement = 0.0;

    // Initial positions: atoms separated by 2.0, rest length 1.0 → stretch of 100%
    rx[1] = 0.0; ry[1] = 0.0;
    rx[2] = 2.0; ry[2] = 0.0;

    // Define bond
    atom1[1] = 1;
    atom2[1] = 2;
    kb[1] = 1.0;
    ro[1] = 1.1;
}

// Cleanup after each test
void Close(void) {
    free(rx); free(ry); free(vx); free(vy);
    free(ax); free(ay);
    free(nodeDragx); free(nodeDragy);
    free(atom1); free(atom2);
    free(kb); free(ro);
    free(BondEnergy); free(BondLength);
}

// Custom assert function for floating point comparisons
void assert_double_within(double expected, double actual, double tol) {
    if (fabs(expected - actual) > tol) {
        printf("Assertion failed: expected %.6f, got %.6f\n", expected, actual);
        exit(1);
    }
}

// The actual test case
void TestComputeBondForce(void) {
    ComputeBondForce();

    // With 100% stretch: F = -k*[(r - r0)/r0] = -1*(2 - 1.1)/1.1 = -0.818181818181818, unit vector is (-1,0)
    // So force on atom 1 is +0.818181818181818 in x, atom 2 is -0.818181818181818 in x
    assert_double_within(0.818181818181818, ax[1], TOL);
    assert_double_within(0.0, ay[1], TOL);
    assert_double_within(-0.818181818181818, ax[2], TOL);
    assert_double_within(0.0, ay[2], TOL);

    // Bond energy = 0.5 * k * r0 * [(r/r0 - 1)^2] = 0.5 * 1 * 1 * (2/1 - 1)^2 = 0.5
    assert_double_within(0.3681818181818181, BondEnergy[1], TOL);

    // Bond length = 2.0
    assert_double_within(2.0, BondLength[1], TOL);

    printf("All tests passed!\n");
}

// Main function to run tests
int main(void) {
    setUp();
    TestComputeBondForce();
    Close();
    return 0;
}


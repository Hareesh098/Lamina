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
 
#include <stdio.h>
#include "../source/global.h"
#include "TestComputeBondForce.h"
#include "../source/ComputeBondForce.h"
#include "assert_double_within.h"

extern const double TOL;

void TestComputeBondForce(void) {
 ComputeBondForce();

 assert_double_within(0.8181818181818181, ax[1], TOL);
 assert_double_within(0.0, ay[1], TOL);
 assert_double_within(-0.8181818181818181, ax[2], TOL);
 assert_double_within(0.0, ay[2], TOL);

 assert_double_within(0.3681818181818181, BondEnergy[1], TOL);
 assert_double_within(2.0, BondLength[1], TOL);

 printf("All tests for bonded interaction passed!\n");
}


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
#include "TestComputePairForce.h"
#include "../source/ComputePairForce.h"
#include "assert_double_within.h"

extern const double TOL;

void TestComputePairForce(int normFlag){
 ComputePairForce(1);

 assert_double_within(0.0, ax[3], TOL);
 assert_double_within(-0.05, ay[3], TOL);
 assert_double_within(0.0, ax[4], TOL);
 assert_double_within(0.05, ay[4], TOL);

 assert_double_within(0.0025/2, uSumPair, TOL);


 printf("All tests for paired interaction passed!\n");
}


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
#include <stdlib.h>
#include <math.h>
#include "../source/global.h"

void assert_double_within(double expected, double actual, double tol) {
    if (fabs(expected - actual) > tol) {
        printf("Assertion failed: expected %.16f, got %.16f\n", expected, actual);
        exit(1);
    }
}


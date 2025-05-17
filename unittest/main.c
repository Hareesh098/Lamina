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
#include "Init.h"
#include "Close.h"
#include "TestComputeBondForce.h"
#include "TestComputePairForce.h"
#define DEFINE_GLOBALS
#include "../source/global.h"

const double TOL = 1e-16;

int main(void) {
 Init();
 TestComputeBondForce();
 TestComputePairForce(1);
 Close();
 return 0;
}


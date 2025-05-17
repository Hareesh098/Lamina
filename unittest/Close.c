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
 
#include <stdlib.h>
#include "../source/global.h"

void Close(void) {
 free(rx); free(ry); free(vx); free(vy);
 free(ax); free(ay);
 free(nodeDragx); free(nodeDragy);
 free(atom1); free(atom2);
 free(kb); free(ro);
 free(BondEnergy); free(BondLength);
}


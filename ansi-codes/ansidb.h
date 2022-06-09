/*
 * Copyright (C) 2021 taylor.fish <contact@taylor.fish>
 *
 * This file is part of rgbto256.
 *
 * rgbto256 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rgbto256 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with rgbto256. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ANSIDB__ANSIDB_H
#define ANSIDB__ANSIDB_H

#include "../color.h"

#define ANSI_MIN           16
#define ANSI_MAX           256
#define ANSI_MAP_OFFSET    ANSI_MIN
#define ANSI_MAP_LEN       (ANSI_MAX - ANSI_MAP_OFFSET)

extern const RGBColor ansi_to_rgb_map[];
extern const LabColor ansi_to_lab_map[];


static inline RGBColor ansi_to_rgb(int ansi_num) {
  return(ansi_to_rgb_map[ansi_num - ANSI_MAP_OFFSET]);
}


static inline LabColor ansi_to_lab(int ansi_num) {
  return(ansi_to_lab_map[ansi_num - ANSI_MAP_OFFSET]);
}

#endif

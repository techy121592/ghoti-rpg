/**
 * Copyright (C) 2018 David Welch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; only version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include "components/primitive-components/drawable-component.h"

class Tile : public DrawableComponent {
    uint32_t z;
public:
    Tile(uint32_t x, uint32_t y, uint32_t z, uint32_t tileIndex, uint32_t tileWidth, uint32_t tileHeight, uint32_t padding, SDL_Texture* texture);
    uint32_t GetZ();
    SDL_Rect GetLocation();
};

#endif

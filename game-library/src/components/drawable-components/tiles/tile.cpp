/**
 * Copyright (C) 2017  David Welch & Ankit Singhania
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
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

#include "components/drawable-components/tiles/tile.h"

Tile::Tile(uint32_t x, uint32_t y, uint32_t tileIndex, uint32_t tileWidth, uint32_t tileHeight, uint32_t padding, SDL_Texture* texture)
    : DrawableComponent(x * tileWidth, y * tileHeight, tileWidth, tileHeight, padding, tileIndex, texture) {

}
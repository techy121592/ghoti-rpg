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

#include "components/drawable-components/tiles/tile_map.h"

TileMap::TileMap(uint32_t rows, uint32_t cols, uint32_t tileWidth, uint32_t tileHeight, std::list<Tile*> tiles, SDL_Renderer* ren)
        : DrawableComponent(cols * tileWidth, rows * tileHeight, ren) {
    this->tiles = std::move(tiles);
    PreRenderMap(ren);
}

void TileMap::PreRenderMap(SDL_Renderer* ren) {
    SDL_SetRenderTarget(ren, texture);
    for(Tile* tile : tiles) {
        tile->Draw(ren);
    }
    SDL_SetRenderTarget(ren, nullptr);
}

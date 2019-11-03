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

#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <utility>
#include <vector>
#include "tile.h"
#include "components/primitive-components/drawable-component.h"
#include "components/primitive-components/rendererable-drawable-component.h"

class TileMap : public Component {
    std::vector<Tile*> tiles;
    void PreRenderMap();
    RenderableDrawableComponent* topLayer;
    RenderableDrawableComponent* bottomLayer;
    uint32_t playerZIndex;
public:
    TileMap(uint32_t rows, uint32_t cols, uint32_t tileWidth, uint32_t tileHeight, uint32_t playerZ, std::vector<Tile*> tiles);
    DrawableComponent* GetTopLayer();
    DrawableComponent* GetBottomLayer();
    std::vector<Tile*> CheckCollision(SDL_Rect targetRectangle);
};

#endif

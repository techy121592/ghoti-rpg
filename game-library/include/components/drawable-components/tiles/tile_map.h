/**
 * Copyright (C) 2018 David Welch
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

#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <list>
#include <utility>
#include "tile.h"
#include "components/primitive-components/drawable_component.h"
#include "components/primitive-components/rendererable_drawable_component.h"

class TileMap : public Component {
    std::list<Tile*> tiles;
    void PreRenderMap();
    RenderableDrawableComponent* topLayer;
    RenderableDrawableComponent* bottomLayer;
    int playerZIndex;
public:
    TileMap(uint32_t rows, uint32_t cols, uint32_t tileWidth, uint32_t tileHeight, uint32_t playerZ, std::list<Tile*> tiles);
    DrawableComponent* GetTopLayer();
    DrawableComponent* GetBottomLayer();
    std::list<Tile*> CheckCollision(SDL_Rect targetRectangle);
};

#endif

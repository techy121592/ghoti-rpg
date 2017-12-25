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

TileMap::TileMap(uint32_t rows, uint32_t cols, uint32_t tileWidth, uint32_t tileHeight, uint32_t playerZIndex, std::list<Tile*> tiles, SDL_Renderer* ren) : Component() {
    topLayer = new RenderableDrawableComponent(cols * tileWidth, rows * tileHeight, ren);
    bottomLayer = new RenderableDrawableComponent(cols * tileWidth, rows * tileHeight, ren);
    this->tiles = std::move(tiles);
    this->playerZIndex = playerZIndex;
    PreRenderMap(ren);
}

void TileMap::PreRenderMap(SDL_Renderer* ren) {
    std::cout << "PlayerZIndex: " << playerZIndex << std::endl;
    PreRenderMap(playerZIndex, ren);

    for(int graphicalLayerCount = 0; graphicalLayerCount < 2; graphicalLayerCount++) {
        SDL_SetRenderTarget(ren, graphicalLayerCount < 1 ?
                                 bottomLayer->GetTexture() :
                                 topLayer->GetTexture());

        bool renderCheck = false;
        std::cout << "Rendering to " << (graphicalLayerCount < 1 ? "bottom layer" : "top layer") << std::endl;

        for(Tile* tile : tiles) {
            if(tile->GetZ() < playerZIndex && graphicalLayerCount == 0 || tile->GetZ() > playerZIndex && graphicalLayerCount == 1) {
                renderCheck = true;
                tile->Draw(ren);
            }
        }

        std::cout << (renderCheck ? "Successfully" : "Failed") << " to render to layer" << std::endl;

        SDL_SetRenderTarget(ren, nullptr);
    }
}

DrawableComponent* TileMap::GetTopLayer() {
    return topLayer;
}

DrawableComponent* TileMap::GetBottomLayer() {
    return bottomLayer;
}

std::list<Tile*> TileMap::CheckCollision(SDL_Rect targetRect) {
    std::list<Tile*> tilesColliding;
    for(auto tile : tiles) {
        auto tileLocation = tile->GetLocation();

        if((targetRect.x >= tileLocation.x && targetRect.x <= tileLocation.x + tileLocation.w ||
                targetRect.x + targetRect.w >= tileLocation.x && targetRect.x + targetRect.w <= tileLocation.x + tileLocation.w) &&
                (targetRect.y >= tileLocation.y && targetRect.y <= tileLocation.y + tileLocation.h ||
                 targetRect.y + targetRect.h >= tileLocation.y && targetRect.y + targetRect.h <= tileLocation.y + tileLocation.h) &&
                tile->GetZ() == playerZIndex - 1) {
            std::cout << "Collision detected" << std::endl;
            tilesColliding.push_back(tile);
        }
    }
    return tilesColliding;
}

DrawableComponent* TileMap::GetTopLayer() {
    return topLayer;
}

DrawableComponent* TileMap::GetBottomLayer() {
    return bottomLayer;
}

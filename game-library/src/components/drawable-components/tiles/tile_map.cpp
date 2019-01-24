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

#include "components/drawable-components/tiles/tile_map.h"

TileMap::TileMap(uint32_t rows, uint32_t cols, uint32_t tileWidth, uint32_t tileHeight, uint32_t playerZIndex, std::list<Tile*> tiles) : Component() {
    topLayer = new RenderableDrawableComponent(cols * tileWidth, rows * tileHeight);
    bottomLayer = new RenderableDrawableComponent(cols * tileWidth, rows * tileHeight);

    this->tiles = std::move(tiles);
    this->playerZIndex = playerZIndex;
    PreRenderMap();
}

void TileMap::PreRenderMap() {
    while(!topLayer->IsReady() || !bottomLayer->IsReady()) {
        SDL_Delay(10);
    }
    auto renderQueue = new RenderQueue();
    for(int graphicalLayerCount = 0; graphicalLayerCount < 2; graphicalLayerCount++) {
        renderQueue->AddSetRenderTarget(graphicalLayerCount < 1 ? bottomLayer->GetTexture() : topLayer->GetTexture(), [](){});
        for(auto tile : tiles) {
            while(!tile->IsReady()) {
                SDL_Delay(10);
            }
            if((tile->GetZ() < playerZIndex && graphicalLayerCount == 0) || (tile->GetZ() > playerZIndex && graphicalLayerCount == 1)) {
                tile->Draw(renderQueue);
            }
        }
    }
    renderQueue->AddSetRenderTarget(nullptr, [this]() {
        ready = true;
    });
    delete renderQueue;
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

        if(((targetRect.x >= tileLocation.x && targetRect.x < tileLocation.x + tileLocation.w) ||
                (targetRect.x + targetRect.w > tileLocation.x && targetRect.x + targetRect.w < tileLocation.x + tileLocation.w)) &&
                ((targetRect.y >= tileLocation.y && targetRect.y < tileLocation.y + tileLocation.h) ||
                        (targetRect.y + targetRect.h > tileLocation.y && targetRect.y + targetRect.h < tileLocation.y + tileLocation.h)) &&
                tile->GetZ() == playerZIndex - 1) {
            tilesColliding.emplace_back(tile);
        }
    }
    return tilesColliding;
}

//
// Created by dwelch on 9/12/17.
//

#include "components/tile.h"

Tile::Tile(uint32_t x, uint32_t y, uint32_t type, uint32_t tileWidth, uint32_t tileHeight, SDL_Texture* texture)
    : DrawableComponent(x * tileWidth, y * tileHeight, tileWidth, tileHeight, type, texture) {

}
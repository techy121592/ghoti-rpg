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

#include "components/drawable-components/character.h"

Character::Character(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t frame, SDL_Texture* texture, float speed)
        : DrawableComponent(x, y, width, height, frame, texture) {
    this->speed = speed;
}

void Character::SetInput(InputData inputData) {
    this->inputData = inputData;
}

void Character::Update(uint32_t deltaTime, TileMap* tileMap) {
    auto amountToMove = (uint32_t)(speed * deltaTime);
    SDL_Rect destinationRectangle = locationRectangle;
    if(inputData.MoveUp) {
        destinationRectangle.y -= amountToMove;
    }
    if(inputData.MoveDown) {
        destinationRectangle.y += amountToMove;
    }
    if(inputData.MoveLeft) {
        destinationRectangle.x -= amountToMove;
    }
    if(inputData.MoveRight) {
        destinationRectangle.x += amountToMove;
    }
    destinationRectangle = CalculateValidPosition(destinationRectangle, tileMap);
    locationRectangle = destinationRectangle;
}

SDL_Rect Character::CalculateValidPosition(SDL_Rect targetRectangle, TileMap* tileMap) {
    auto collidingTiles = tileMap->CheckCollision(targetRectangle);
    if(!collidingTiles.empty()) {
        return locationRectangle;
    }
    return targetRectangle;
}

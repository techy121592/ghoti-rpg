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

#include "components/drawable-components/character.h"

Character::Character(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t frame, std::string path, float speed)
        : DrawableComponent(x, y, width, height, frame, path) {
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
    locationRectangle = CalculateValidPosition(destinationRectangle, tileMap);
}

SDL_Rect Character::DealWithHorizontalOverlap(SDL_Rect targetRectangle, SDL_Rect tileRectangle) {
    auto newTargetRectangle = targetRectangle;
    if(locationRectangle.x + locationRectangle.w <= tileRectangle.x &&
       newTargetRectangle.x + newTargetRectangle.w > tileRectangle.x) {
        // Started to the left of tile & now colliding on given axis
        newTargetRectangle.x = tileRectangle.x - newTargetRectangle.w;
    } else if(locationRectangle.x >= tileRectangle.x + tileRectangle.w &&
              newTargetRectangle.x < tileRectangle.x + tileRectangle.w) {
        // Started to the right of tile & now colliding on given axis
        newTargetRectangle.x = tileRectangle.x + tileRectangle.w;
    }
    return newTargetRectangle;
}

SDL_Rect Character::DealWithVerticalOverlap(SDL_Rect targetRectangle, SDL_Rect tileRectangle) {
    auto newTargetRectangle = targetRectangle;
    if(locationRectangle.y + locationRectangle.h <= tileRectangle.y &&
           newTargetRectangle.y + newTargetRectangle.h > tileRectangle.y) {
        // Started above tile & now colliding on given axis
        newTargetRectangle.y = tileRectangle.y - newTargetRectangle.h;
    } else if(locationRectangle.y >= tileRectangle.y + tileRectangle.h &&
              newTargetRectangle.y < tileRectangle.y + tileRectangle.h) {
        // Started bellow tile & now colliding on given axis
        newTargetRectangle.y = tileRectangle.y + tileRectangle.h;
    }
    return newTargetRectangle;
}

SDL_Rect Character::CalculateValidPosition(SDL_Rect targetRectangle, TileMap* tileMap) {
    auto newTargetRectangle = targetRectangle;
    auto collidingTiles = tileMap->CheckCollision(targetRectangle);
    for(auto tile : collidingTiles) {
        auto tileRectangle = tile->GetLocation();

        newTargetRectangle = DealWithHorizontalOverlap(targetRectangle, tileRectangle);
        auto newSetOfCollidingTiles = tileMap->CheckCollision(newTargetRectangle);
        if(newSetOfCollidingTiles.empty()) {
            break;
        }

        newTargetRectangle = DealWithVerticalOverlap(targetRectangle, tileRectangle);
        newSetOfCollidingTiles = tileMap->CheckCollision(newTargetRectangle);
        if(newSetOfCollidingTiles.empty()) {
            break;
        }

        newTargetRectangle = DealWithHorizontalOverlap(newTargetRectangle, tileRectangle);
        newSetOfCollidingTiles = tileMap->CheckCollision(newTargetRectangle);
        if(newSetOfCollidingTiles.empty()) {
            break;
        }
        return locationRectangle;
    }
    return newTargetRectangle;
}

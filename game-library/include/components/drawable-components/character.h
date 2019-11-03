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

#ifndef CHARACTER_H
#define CHARACTER_H

#include "components/primitive-components/drawable-component.h"
#include "components/drawable-components/tiles/tile-map.h"
#include "utilities/input/input-data.h"

class Character : public DrawableComponent {
    float speed;
    InputData inputData;
    SDL_Rect CalculateValidPosition(SDL_Rect targetRectangle, TileMap* tileMap);
    SDL_Rect DealWithHorizontalOverlap(SDL_Rect targetRectangle, SDL_Rect tileRectangle);
    SDL_Rect DealWithVerticalOverlap(SDL_Rect targetRectangle, SDL_Rect tileRectangle);
public:
    Character(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t frame, std::string path, float speed);
    void SetInput(InputData inputData);
    void Update(uint32_t deltaTime, TileMap* tileMap);
};

#endif

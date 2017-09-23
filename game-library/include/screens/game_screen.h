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

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SDL.h>
#include "utilities/resource_loader.h"
#include "screen.h"
#include "components/tile.h"
#include "components/tile_set.h"
#include "components/tile_map.h"

class GameScreen : public Screen {
public:
    explicit GameScreen(SDL_Renderer* ren);
    ~GameScreen();
    void Setup();
    bool CheckSetup();
    void Update(uint32_t deltaTime, InputData inputData);
};

#endif

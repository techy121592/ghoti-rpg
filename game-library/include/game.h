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

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <tuple>
#include <list>
#include <SDL.h>
#include "utilities/resource_loader.h"
#include "utilities/input_data.h"
#include "utilities/input_processor.h"
#include "utilities/thread_pool.h"
#include "components/drawable_component.h"
#include "screens/screen.h"
#include "screens/game_screen.h"
#include "screens/load_screen.h"

class Game {
private:
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    static Screen* screen;
    uint32_t fps;

    std::tuple<SDL_Window*, SDL_Renderer*> SetupSDL(uint32_t width, uint32_t height);
    void CloseSDL(SDL_Window*& win, SDL_Renderer*& ren, Screen*& screen);
    void PauseForRestOfFrame(uint32_t targetFrameLength, uint32_t deltaTime);
    void FireOffThreadsToUpdateAndGetInput(Screen* screenPointer, uint32_t deltaTime, InputData inputData);
    void Draw(std::list<DrawableComponent*> drawableComponentsData);
    bool Step(uint32_t deltaTime);
    bool GameLoop();
public:
    Game(uint32_t width, uint32_t height, uint32_t maxFPS);
    ~Game();
    int Run();
};

#endif

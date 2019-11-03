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

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <SDL.h>
#include "utilities/resource/resource-loader.h"
#include "utilities/input/input-data.h"
#include "utilities/input/input-processor.h"
#include "utilities/thread-pool.h"
#include "utilities/render-queue.h"
#include "components/primitive-components/drawable-component.h"
#include "screens/screen.h"
#include "screens/main-menu-screen.h"
#include "screens/load-screen.h"

class Game {
private:
    SDL_Window *win = nullptr;
    static Screen* screen;
    uint32_t fps;

    SDL_Window* SetupSDL(uint32_t width, uint32_t height);
    void CloseSDL(SDL_Window*& win, Screen*& screen);
    void PauseForRestOfFrame(uint32_t targetFrameLength, uint32_t deltaTime);
    void FireOffThreadsToUpdateAndGetInput(Screen* screenPointer, uint32_t deltaTime, InputData inputData);
    void Draw(const std::vector<DrawableComponent*>& drawableComponentsData);
    bool Step(uint32_t deltaTime);
    bool GameLoop();
public:
    Game(uint32_t width, uint32_t height, uint32_t maxFPS);
    ~Game();
    int Run();
};

#endif

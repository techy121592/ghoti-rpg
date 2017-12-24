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

#ifndef HELLO_SCREEN_H
#define HELLO_SCREEN_H

#include <SDL.h>
#include "utilities/resource/resource_loader.h"
#include "screen.h"

class HelloScreen : public Screen {
private:
    SDL_Texture* helloTexture;
public:
    explicit HelloScreen(SDL_Renderer* ren);
    ~HelloScreen();
    void Setup();
    bool CheckSetup();
    void Update(uint32_t deltaTime, InputData inputData);
};

#endif

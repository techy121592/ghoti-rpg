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

#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include "screen.h"
#include "hello_screen.h"
#include "resource_loader.h"
#include "thread_pool.h"

template<class T>
class LoadScreen : public Screen {
private:
    static Screen* nextScreenHolder;
    static bool doneLoading;
    SDL_Texture* loadingTexture;
public:
    LoadScreen<T>(SDL_Renderer* ren);
    ~LoadScreen();
    bool CheckSetup();
    void Update(const uint32_t deltaTime, const InputData inputData);
};

#endif

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

#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include "screen.h"
#include "hello_screen.h"
#include "game_screen.h"
#include "utilities/resource/resource_loader.h"
#include "utilities/thread_pool.h"

template<class T>
class LoadScreen : public Screen {
private:
    static Screen* nextScreenHolder;
    static bool doneLoading;
public:
    explicit LoadScreen<T>(SDL_Renderer* ren);
    ~LoadScreen() override;
    void Setup() override;
    bool CheckSetup() override;
    void Update(uint32_t deltaTime, InputData inputData) override;
};

#endif

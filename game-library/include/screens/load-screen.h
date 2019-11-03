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

#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include "screen.h"
#include "hello-screen.h"
#include "game-screen.h"
#include "main-menu-screen.h"
#include "utilities/resource/resource-loader.h"
#include "utilities/thread-pool.h"

template<class T>
class LoadScreen : public Screen {
public:
    LoadScreen();
    void Update(uint32_t deltaTime, InputData inputData) override;
};

#endif

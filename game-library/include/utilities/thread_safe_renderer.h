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

#ifndef THREAD_SAFE_RENDERER_H
#define THREAD_SAFE_RENDERER_H

#include <mutex>
#include <SDL.h>

class ThreadSafeRenderer {
    static SDL_Renderer* renderer;
    static std::mutex rendererLock;
public:
    SDL_Renderer* Renderer;

    ThreadSafeRenderer();
    ~ThreadSafeRenderer();
    static void SetUpRenderer(SDL_Window* win);
};

#endif

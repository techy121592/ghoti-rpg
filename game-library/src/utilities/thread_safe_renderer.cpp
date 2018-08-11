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

#include <iostream>
#include "utilities/thread_safe_renderer.h"

SDL_Renderer* ThreadSafeRenderer::renderer;
std::mutex ThreadSafeRenderer::rendererLock;

ThreadSafeRenderer::ThreadSafeRenderer() {
    if(renderer == nullptr) throw std::runtime_error("Renderer needs to be set up before it can be locked.");
    rendererLock.lock();
    Renderer = renderer;
}

ThreadSafeRenderer::~ThreadSafeRenderer() {
    rendererLock.unlock();
}

void ThreadSafeRenderer::SetUpRenderer(SDL_Window *win) {
    if(renderer == nullptr) {
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr) {
            SDL_DestroyWindow(win);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
    }
}
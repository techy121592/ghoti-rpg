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
#include "utilities/render_queue.h"

RenderQueue::RenderQueue() {
    queueLock.lock();
}

RenderQueue::~RenderQueue() {
    queueLock.unlock();
}

void RenderQueue::Add(RendererAction action, void* data) {
    queue.emplace_back(RenderQueueEntry(action, data));
}

void RenderQueue::WatchLoop() {
    SDL_Renderer* renderer;
    while(running) {
        if(queue.size() > 0) {
            queueLock.lock();
            auto currentEntry = queue.front();
            queue.pop_front();
            queueLock.unlock();
            ProcessEntry(currentEntry, renderer);
        } else {
            SDL_Delay(1);
        }
    }
}

void RenderQueue::ProcessEntry(RenderQueue::RenderQueueEntry entry, SDL_Renderer* renderer) {
    switch(entry.Action) {
        case SetUpRenderer:
            CreateRenderer((SDL_Window*)entry.Data, renderer);
            break;
        case Draw:
            break;
    }
}

void RenderQueue::StartQueueWatcher() {
    std::thread(WatchLoop);
}

void RenderQueue::StopQueueWatcher() {
    running = false;
}

void RenderQueue::CreateRenderer(SDL_Window *win, SDL_Renderer* renderer) {
    if(renderer == nullptr) {
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr) {
            SDL_DestroyWindow(win);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
    }
}
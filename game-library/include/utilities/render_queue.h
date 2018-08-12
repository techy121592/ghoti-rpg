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

#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <list>
#include <mutex>
#include <thread>
#include <SDL.h>

enum RendererAction {
    SetUpRenderer,
    Draw,

};

class RenderQueue {
    struct RenderQueueEntry {
        RendererAction Action;
        void* Data;
        RenderQueueEntry(RendererAction action, void* data) {
            Action = action;
            Data = data;
        }
    };

    static std::list<RenderQueueEntry> queue;
    static std::mutex queueLock;
    static bool running;
    static void WatchLoop();
    static void ProcessEntry(RenderQueueEntry entry, SDL_Renderer* renderer);
    static void CreateRenderer(SDL_Window *win, SDL_Renderer* renderer);

public:
    RenderQueue();
    ~RenderQueue();
    static void StartQueueWatcher();
    static void StopQueueWatcher();
    void Add(RendererAction action, void* data = nullptr);
};

#endif

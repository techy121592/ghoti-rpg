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

#include <functional>
#include <list>
#include <mutex>
#include <thread>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class RenderQueue {
    enum RendererAction {
        SetUpRenderer,
        ConvertSurfaceToTexture,
        CreateTexture,
        Draw,
        Clear,
        Present,
        SetRenderTarget,
        QueryTexture
    };

    struct DrawInfo {
        SDL_Texture* texture;
        SDL_Rect sourceRect, destRect;
        DrawInfo(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect) {
            this->texture = texture;
            this->sourceRect = sourceRect;
            this->destRect = destRect;
        }
    };

    struct TextureInfo {
        uint32_t format;
        int access, width, height;
    };

    struct RenderQueueEntry {
        RendererAction action;
        void* data;
        std::function<void(void*)> callback;
        RenderQueueEntry(RendererAction action, void* data, std::function<void(void*)> callback) {
            this->action = action;
            this->data = data;
            this->callback = callback;
        }
    };

    static std::list<RenderQueueEntry> queue;
    static std::mutex queueLock;
    static SDL_Renderer* renderer;
    static bool running;

    static void WatchLoop();
    static void ProcessEntry(RenderQueueEntry entry);
    static void CreateRenderer(SDL_Window *win);

public:
    RenderQueue();
    ~RenderQueue();
    static void StartQueueWatcher();
    static void StopQueueWatcher();
    static void AddSetUpRenderer(SDL_Window* window, std::function<void()> callback);
    static void AddConvertSurfaceToTexture(SDL_Surface* surface, std::function<void(SDL_Texture*)> callback);
    static void AddCreateTexture(SDL_Point* size, std::function<void(SDL_Texture*)> callback);
    static void AddDraw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect, std::function<void()> callback);
    static void AddClear(std::function<void()> callback);
    static void AddPresent(std::function<void()> callback);
    static void AddSetRenderTarget(SDL_Texture* texture, std::function<void()> callback);
    static void AddQueryTexture(SDL_Texture* texture, std::function<void(uint32_t, int, int, int)> callback);
    static bool IsEmpty();
};

#endif

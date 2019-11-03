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

#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <functional>
#include <vector>
#include <algorithm>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>
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
        SDL_Rect sourceRect{}, destRect{};
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
        RenderQueueEntry(RendererAction action, void* data, const std::function<void(void*)>& callback) {
            this->action = action;
            this->data = data;
            this->callback = callback;
        }
    };

    static std::vector<RenderQueueEntry> queue;
    static std::mutex queueLock;
    static SDL_Renderer* renderer;
    static bool running;

    static void WatchLoop();
    static void ProcessEntry(const RenderQueueEntry& entry);
    static void CreateRenderer(SDL_Window *win);
    static void AddSetUpRendererStatic(SDL_Window* window, const std::function<void()>& callback);
    static void AddConvertSurfaceToTextureStatic(SDL_Surface* surface, const std::function<void(SDL_Texture*)>& callback);
    static void AddCreateTextureStatic(SDL_Point* size, const std::function<void(SDL_Texture*)>& callback);
    static void AddDrawStatic(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect, const std::function<void()>& callback);
    static void AddClearStatic(const std::function<void()>& callback);
    static void AddPresentStatic(const std::function<void()>& callback);
    static void AddSetRenderTargetStatic(SDL_Texture* texture, const std::function<void()>& callback);
    static void AddQueryTextureStatic(SDL_Texture* texture, const std::function<void(uint32_t, int, int, int)>& callback);

public:
    RenderQueue();
    ~RenderQueue();
    static void StartQueueWatcher();
    static void StopQueueWatcher();
    void AddSetUpRenderer(SDL_Window* window, const std::function<void()>& callback);
    void AddConvertSurfaceToTexture(SDL_Surface* surface, const std::function<void(SDL_Texture*)>& callback);
    void AddCreateTexture(SDL_Point* size, const std::function<void(SDL_Texture*)>& callback);
    void AddDraw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect, const std::function<void()>& callback);
    void AddClear(const std::function<void()>& callback);
    void AddPresent(const std::function<void()>& callback);
    void AddSetRenderTarget(SDL_Texture* texture, const std::function<void()>& callback);
    void AddQueryTexture(SDL_Texture* texture, const std::function<void(uint32_t, int, int, int)>& callback);
    static bool IsEmpty();
};

#endif

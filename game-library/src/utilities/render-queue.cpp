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

#include "utilities/render-queue.h"

std::mutex RenderQueue::queueLock;
bool RenderQueue::running;
SDL_Renderer* RenderQueue::renderer;
std::list<RenderQueue::RenderQueueEntry> RenderQueue::queue;

RenderQueue::RenderQueue() {
    queueLock.lock();
}

RenderQueue::~RenderQueue() {
    queueLock.unlock();
}

void RenderQueue::AddSetUpRenderer(SDL_Window* window, std::function<void()> callback) {
    queue.emplace_back(RenderQueueEntry(RendererAction::SetUpRenderer, window, [callback](void* data) {
        callback();
    }));
}

void RenderQueue::AddConvertSurfaceToTexture(SDL_Surface* surface, std::function<void(SDL_Texture*)> callback) {
    queue.emplace_back(RenderQueueEntry(RendererAction::ConvertSurfaceToTexture, surface, [callback](void* data) {
        callback((SDL_Texture*)data);
    }));
}

void RenderQueue::AddCreateTexture(SDL_Point* size, std::function<void(SDL_Texture*)> callback) {
    queue.emplace_back(RenderQueueEntry(RendererAction::CreateTexture, size, [callback](void* data) {
        callback((SDL_Texture*)data);
    }));
}

void RenderQueue::AddDraw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect, std::function<void()> callback) {
    queue.emplace_back(RendererAction::Draw, new DrawInfo(texture, sourceRect, destRect), [callback](void* data) {
        callback();
    });
}

void RenderQueue::AddClear(std::function<void()> callback) {
    queue.emplace_back(RenderQueueEntry(RendererAction::Clear, nullptr, [callback](void* data) {
        callback();
    }));
}

void RenderQueue::AddPresent(std::function<void()> callback) {
    queue.emplace_back(RenderQueueEntry(RendererAction::Present, nullptr, [callback](void* data) {
        callback();
    }));
}

void RenderQueue::AddSetRenderTarget(SDL_Texture* texture, std::function<void()> callback) {
    queue.emplace_back(RenderQueueEntry(RendererAction::SetRenderTarget, texture, [callback](void* data) {
        callback();
    }));
}

void RenderQueue::AddQueryTexture(SDL_Texture* texture, std::function<void(uint32_t, int, int, int)> callback) {
    queue.emplace_back(RendererAction::QueryTexture, texture, [callback](void* data) {
        auto textureInfo = static_cast<TextureInfo*>(data);
        callback(textureInfo->format, textureInfo->access, textureInfo->width, textureInfo->height);
    });
}

void RenderQueue::WatchLoop() {
    while(running) {
        if(!queue.empty()) {
            queueLock.lock();
            auto currentEntry = queue.front();
            queue.pop_front();
            queueLock.unlock();
            ProcessEntry(currentEntry);
        } else {
            SDL_Delay(1);
        }
    }
    if(renderer != nullptr) SDL_DestroyRenderer(renderer);
}

void RenderQueue::ProcessEntry(RenderQueue::RenderQueueEntry entry) {
    void* output = nullptr;
    switch(entry.action) {
        case RendererAction::SetUpRenderer:
            CreateRenderer(static_cast<SDL_Window*>(entry.data));
            break;
        case RendererAction::ConvertSurfaceToTexture:
            output = SDL_CreateTextureFromSurface(renderer, static_cast<SDL_Surface*>(entry.data));
            break;
        case RendererAction::CreateTexture:
        {
            auto size = static_cast<SDL_Point*>(entry.data);
            output = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, size->x, size->y);
            break;
        }
        case RendererAction::Draw:
        {
            auto drawInfo = static_cast<DrawInfo*>(entry.data);
            SDL_RenderCopy(renderer, drawInfo->texture, &drawInfo->sourceRect, &drawInfo->destRect);
            break;
        }
        case RendererAction::Clear:
            SDL_RenderClear(renderer);
            break;
        case RendererAction::Present:
            SDL_RenderPresent(renderer);
            break;
        case RendererAction::SetRenderTarget:
            SDL_SetRenderTarget(renderer, (SDL_Texture*)entry.data);
            break;
        case RendererAction::QueryTexture:
        {
            auto textureInfo = new TextureInfo();
            SDL_QueryTexture(static_cast<SDL_Texture*>(entry.data), &textureInfo->format, &textureInfo->access, &textureInfo->width, &textureInfo->height);
            output = textureInfo;
            break;
        }
    }
    if(entry.callback != nullptr) {
        entry.callback(output);
    }
}

void RenderQueue::StartQueueWatcher() {
    static auto loopThread = std::thread([] {
        running = true;
        WatchLoop();
    });
}

void RenderQueue::StopQueueWatcher() {
    running = false;
}

void RenderQueue::CreateRenderer(SDL_Window *win) {
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

bool RenderQueue::IsEmpty() {
    return queue.empty();
}
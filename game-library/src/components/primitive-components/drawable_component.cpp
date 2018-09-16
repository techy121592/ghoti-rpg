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

#include <SDL_image.h>
#include <utilities/resource/resource_loader.h>
#include "components/primitive-components/drawable_component.h"

DrawableComponent::DrawableComponent(int32_t width, int32_t height) {
    auto size = new SDL_Point();
    size->x = width;
    size->y = height;
    texture = nullptr;
    auto renderQueue = new RenderQueue();
    renderQueue->AddCreateTexture(size, [this](void* data){
        texture =  (SDL_Texture*)data;
        ready = true;
    });
    delete renderQueue;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    locationRectangle = rect;
    sourceRectangle = rect;
}

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t frame, std::string path)
        : DrawableComponent(x, y, width, height, 0, frame, path) {
}

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t padding, int32_t frame, std::string path) {
    auto surface = ResourceLoader::LoadImage(path);
    auto renderQueue = new RenderQueue();
    renderQueue->AddConvertSurfaceToTexture(surface, [this, x, y, width, height, padding, frame, path](void* data){
        texture = (SDL_Texture*)data;
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        auto renderQueue = new RenderQueue();
        renderQueue->AddQueryTexture(texture, [this, x, y, width, height, padding, frame](uint32_t format, int access, int textureWidth, int textureHeight) {
            int32_t framesWide = (textureWidth + padding) / (width + padding);

            sourceRectangle = {(frame%framesWide) * (width + padding), (frame/framesWide) * (height + padding), width, height};
            locationRectangle = {x, y, width, height};
            ready = true;
        });
        delete renderQueue;
    });
    delete renderQueue;
}

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t padding, int32_t frame, SDL_Texture* texture) {
    this->texture = texture;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    auto renderQueue = new RenderQueue();
    renderQueue->AddQueryTexture(texture, [this, texture, x, y, width, height, padding, frame](uint32_t format, int access, int textureWidth, int textureHeight) {
        int32_t framesWide = (textureWidth + padding) / (width + padding);
        sourceRectangle = {(frame%framesWide) * (width + padding), (frame/framesWide) * (height + padding), width, height};
        locationRectangle = {x, y, width, height};
        ready = true;
    });
    delete renderQueue;
}

DrawableComponent::DrawableComponent(const SDL_Rect locationRectangle, const SDL_Rect sourceRectangle, SDL_Texture* texture) {
    this->locationRectangle = locationRectangle;
    this->sourceRectangle = sourceRectangle;
    this->texture = texture;
    this->ready = true;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

DrawableComponent::~DrawableComponent() {
    SDL_DestroyTexture(texture);
}

void DrawableComponent::Draw(RenderQueue* renderQueue) {
    renderQueue->AddDraw(texture, sourceRectangle, locationRectangle, [](){});
}

DrawableComponent* DrawableComponent::Clone() {
    return new DrawableComponent(locationRectangle, sourceRectangle, texture);
}

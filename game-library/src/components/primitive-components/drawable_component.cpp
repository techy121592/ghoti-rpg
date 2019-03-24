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
        texture =  static_cast<SDL_Texture*>(data);
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

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t frame, const std::string path)
        : DrawableComponent(x, y, width, height, 0, frame, path) {
}

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t padding, int32_t frame, std::string path) {
    this->padding = padding;
    auto surface = ResourceLoader::LoadImage(path);
    auto renderQueue = new RenderQueue();
    renderQueue->AddConvertSurfaceToTexture(surface, [this, x, y, width, height, frame, path](void* data){
        texture = static_cast<SDL_Texture*>(data);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        sourceRectangle.w = width;
        sourceRectangle.h = height;
        auto renderQueue = new RenderQueue();
        renderQueue->AddQueryTexture(texture, [this, x, y, width, height, frame](uint32_t format, int32_t access, int32_t textureWidth, int32_t textureHeight) {
            this->textureWidth = textureWidth;
            this->textureHeight = textureHeight;
            sourceRectangle = CalculateFrameLocation((uint32_t)frame);
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
    this->padding = padding;
    sourceRectangle.w = width;
    sourceRectangle.h = height;
    renderQueue->AddQueryTexture(texture, [this, x, y, width, height, frame](uint32_t format, int access, int textureWidth, int textureHeight) {
        this->textureWidth = textureWidth;
        this->textureHeight = textureHeight;
        sourceRectangle = CalculateFrameLocation((uint32_t)frame);
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

void DrawableComponent::SetFrame(uint32_t frame) {
    sourceRectangle = CalculateFrameLocation(frame);
}

SDL_Rect DrawableComponent::CalculateFrameLocation(uint32_t frame) {
    int32_t framesWide = (textureWidth + padding) / (sourceRectangle.w + padding);
    return {
        (static_cast<int32_t>(frame%framesWide)) * (sourceRectangle.w + padding),
        (static_cast<int32_t>(frame/framesWide)) * (sourceRectangle.h + padding),
        sourceRectangle.w,
        sourceRectangle.h
    };
}

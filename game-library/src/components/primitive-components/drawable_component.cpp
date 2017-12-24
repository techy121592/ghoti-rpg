/**
 * Copyright (C) 2017  David Welch & Ankit Singhania
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

#include "components/primitive-components/drawable_component.h"

DrawableComponent::DrawableComponent(int32_t width, int32_t height, SDL_Renderer* ren)
        : DrawableComponent(0, 0, width, height, 0, SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height)) {
}

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t frame, SDL_Texture* texture)
        : DrawableComponent(x, y, width, height, 0, frame, texture) {
}

DrawableComponent::DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t padding, int32_t frame, SDL_Texture* texture) {
    this->texture = texture;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    int32_t textureWidth, textureHeight;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &textureWidth, &textureHeight);

    int32_t framesWide = (textureWidth + padding) / (width + padding);

    this->sourceRectangle = {(frame%framesWide) * (width + padding), (frame/framesWide) * (height + padding), width, height};
    this->locationRectangle = {x, y, width, height};
}

DrawableComponent::DrawableComponent(const SDL_Rect locationRectangle, const SDL_Rect sourceRectangle, SDL_Texture* texture) {
    this->locationRectangle = locationRectangle;
    this->sourceRectangle = sourceRectangle;
    this->texture = texture;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

DrawableComponent::~DrawableComponent() {
    std::cout << "Destroying texture" << std::endl;
    SDL_DestroyTexture(texture);
}

void DrawableComponent::Draw(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, texture, &sourceRectangle, &locationRectangle);
}

DrawableComponent* DrawableComponent::Clone() {
    return new DrawableComponent(locationRectangle, sourceRectangle, texture);
}

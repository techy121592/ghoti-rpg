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

#include "components/drawable_component.h"
#include <iostream>

DrawableComponent::DrawableComponent(const int32_t x, const int32_t y, const int32_t width, const int32_t height, const int32_t frame, SDL_Texture* texture) {
    this->texture = texture;

    int32_t textureWidth, textureHeight;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &textureWidth, &textureHeight);

    uint16_t framesWide = textureWidth / width;

    this->sourceRectangle = {(frame%framesWide) * width, (frame/framesWide) * height, width, height};
    this->destinationRectangle = {x, y, width, height};
}

DrawableComponent::DrawableComponent(const SDL_Rect destinationRectangle, const SDL_Rect sourceRectangle, SDL_Texture* texture) {
    this->destinationRectangle = destinationRectangle;
    this->sourceRectangle = sourceRectangle;
    this->texture = texture;
}

DrawableComponent::~DrawableComponent() {
    SDL_DestroyTexture(texture);
}

void DrawableComponent::Draw(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, texture, &sourceRectangle, &destinationRectangle);
}

DrawableComponent* DrawableComponent::Clone() {
    return new DrawableComponent(sourceRectangle, destinationRectangle, texture);
}

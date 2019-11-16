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

#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include <iostream>
#include <SDL2/SDL.h>
#include "utilities/render-queue.h"
#include "component.h"

class DrawableComponent : public Component {
private:
    SDL_Rect sourceRectangle{};
    int32_t textureWidth{}, textureHeight{}, padding{};
    SDL_Rect CalculateFrameLocation(uint32_t frame);
protected:
    SDL_Texture* texture;
    SDL_Rect locationRectangle{};
    void SetFrame(uint32_t frame);
public:
    DrawableComponent(int32_t width, int32_t height);
    DrawableComponent(SDL_Rect locationRectangle, SDL_Rect sourceRectangle, SDL_Texture* texture);
    DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t frame, const std::string& path);
    DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t padding, int32_t frame, const std::string& path);
    DrawableComponent(int32_t x, int32_t y, int32_t width, int32_t height, int32_t padding, int32_t frame, SDL_Texture* texture);
    ~DrawableComponent() override;
    void Draw(RenderQueue* renderQueue);
    DrawableComponent* Clone();
};

#endif

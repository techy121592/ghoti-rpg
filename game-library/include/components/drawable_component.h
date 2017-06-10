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

#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include <SDL.h>

class DrawableComponent {
private:
    SDL_Texture* texture;
    SDL_Rect sourceRectangle, destinationRectangle;
public:
    DrawableComponent(const SDL_Rect destinationRectangle, const SDL_Rect sourceRectangle, SDL_Texture* texture);
    DrawableComponent(const int32_t x, const int32_t y, const int32_t width, const int32_t height, const int32_t frame, SDL_Texture* texture);
    ~DrawableComponent();
    void Draw(SDL_Renderer* ren);
    DrawableComponent* Clone();
};

#endif

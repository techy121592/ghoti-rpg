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

#include "components/drawable-components/button.h"

Button::Button(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t defaultFrame, uint32_t selectedFrame, const std::string path,
               const std::function<void()> onClick)
        : DrawableComponent(x, y, width, height, defaultFrame, path) {
    this->onClick = onClick;
    this->defaultFrame = defaultFrame;
    this->selectedFrame = selectedFrame;
}

void Button::Click() {
    onClick();
}

void Button::Select() {
    if(!selected) {
        selected = true;
        SetFrame(selectedFrame);
    }
}

void Button::Unselect() {
    if(selected) {
        selected = false;
        SetFrame(defaultFrame);
    }
}

bool Button::WithinButton(SDL_Point point) {
    return point.x >= locationRectangle.x && point.x <= locationRectangle.x + locationRectangle.w &&
            point.y >= locationRectangle.y && point.y <= locationRectangle.y + locationRectangle.h;
}

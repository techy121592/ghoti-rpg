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

Button::Button(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t frame, std::string path,
               std::function<void()> onClick)
        : DrawableComponent(x, y, width, height, frame, path) {
    std::cout << "Initiating button" << std::endl;
    this->onClick = onClick;
}

void Button::Click() {
    onClick();
}

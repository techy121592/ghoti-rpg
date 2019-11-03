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

#include "settings/button-settings.h"

#include <utility>

ButtonSettings::ButtonSettings(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t defaultFrame,
        uint32_t selectedFrame, std::string imagePath, ButtonType buttonType, bool defaultButton,
        std::string above, std::string below, std::string left, std::string right, std::string name) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->defaultFrame = defaultFrame;
    this->selectedFrame = selectedFrame;
    this->imagePath = std::move(imagePath);
    this->buttonType = buttonType;
    this->defaultButton = defaultButton;
    this->above = std::move(above);
    this->below = std::move(below);
    this->left = std::move(left);
    this->right = std::move(right);
    this->name = std::move(name);
}

uint32_t ButtonSettings::GetX() {
    return x;
}

uint32_t ButtonSettings::GetY() {
    return y;
}

uint32_t ButtonSettings::GetWidth() {
    return width;
}

uint32_t ButtonSettings::GetHeight() {
    return height;
}

uint32_t ButtonSettings::GetDefaultFrame() {
    return defaultFrame;
}

uint32_t ButtonSettings::GetSelectedFrame() {
    return selectedFrame;
}

std::string ButtonSettings::GetImagePath() {
    return imagePath;
}

ButtonType ButtonSettings::GetButtonType() {
    return buttonType;
}

bool ButtonSettings::IsDefault() {
    return defaultButton;
}

std::string ButtonSettings::GetAbove() {
    return above;
}

std::string ButtonSettings::GetBelow() {
    return below;
}

std::string ButtonSettings::GetLeft() {
    return left;
}

std::string ButtonSettings::GetRight() {
    return right;
}

std::string ButtonSettings::GetName() {
    return name;
}

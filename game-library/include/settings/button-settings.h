/**
 * Copyright (C) 2019 David Welch
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

#ifndef BUTTON_SETTINGS_H
#define BUTTON_SETTINGS_H

#include <string>
#include "button-type.h"

class ButtonSettings {
private:
    uint32_t x, y, width, height, defaultFrame, selectedFrame;
    std::string imagePath, above, below, left, right, name;
    ButtonType buttonType;
    bool defaultButton;
public:
    ButtonSettings(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t defaultFrame,
            uint32_t selectedFrame, std::string imagePath, ButtonType buttonType, bool defaultButton,
            std::string above, std::string below, std::string left, std::string right, std::string name);
    uint32_t GetX();
    uint32_t GetY();
    uint32_t GetWidth();
    uint32_t GetHeight();
    uint32_t GetDefaultFrame();
    uint32_t GetSelectedFrame();
    std::string GetImagePath();
    ButtonType GetButtonType();
    bool IsDefault();
    std::string GetAbove();
    std::string GetBelow();
    std::string GetLeft();
    std::string GetRight();
    std::string GetName();
};

#endif

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

#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include <map>
#include "screen.h"
#include "load-screen.h"
#include "game-screen.h"
#include "components/drawable-components/button.h"

class MainMenuScreen : public Screen {
    Button* defaultButton;
    bool defaultButtonSelected = false;
public:
    MainMenuScreen();
    void Update(uint32_t deltaTime, InputData inputData) override;
};

#endif

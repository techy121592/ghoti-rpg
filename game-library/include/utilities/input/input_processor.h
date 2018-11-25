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

#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <iostream>
#include <list>
#include <SDL.h>
#include "input_processor.h"
#include "input_data.h"

class InputProcessor {
private:
    static InputData inputData;

    static InputData ProcessKeyEvent(SDL_Keycode keycode, InputData inputData, bool keyDown);
    static InputData ProcessMouseLeftClick(int32_t x, int32_t y, InputData inputData, bool pressed);
    static InputData ProcessControllerButtonEvent(uint8_t button, InputData inputData, bool pressed);
public:
    static InputData GetInputData();
    static void GetInputFromDevice();
};

#endif

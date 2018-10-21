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

#include "utilities/input/input_processor.h"

InputData InputProcessor::inputData;

InputData InputProcessor::ProcessKeyEvent(const SDL_Keycode keycode, InputData inputData, const bool keyDown) {
    switch(keycode) {
        case SDLK_ESCAPE:
            inputData.Quit = keyDown;
            break;
        case SDLK_UP: case SDLK_w:
            inputData.MoveUp = keyDown;
            break;
        case SDLK_DOWN: case SDLK_s:
            inputData.MoveDown = keyDown;
            break;
        case SDLK_LEFT: case SDLK_a:
            inputData.MoveLeft = keyDown;
            break;
        case SDLK_RIGHT: case SDLK_d:
            inputData.MoveRight = keyDown;
            break;
        default:
            break;
    }
    return inputData;
}

InputData InputProcessor::ProcessMouseLeftClick(int32_t x, int32_t y, InputData inputData, bool pressed) {
    inputData.LeftClick.X = x;
    inputData.LeftClick.Y = y;
    inputData.LeftClick.Clicked = pressed;
    return inputData;
}

InputData InputProcessor::GetInputData() {
    return inputData;
}

void InputProcessor::GetInputFromDevice() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                inputData.Quit = true;
                break;
            case SDL_KEYDOWN:
                inputData = ProcessKeyEvent(event.key.keysym.sym, inputData, true);
                break;
            case SDL_KEYUP:
                inputData = ProcessKeyEvent(event.key.keysym.sym, inputData, false);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    inputData = ProcessMouseLeftClick(event.button.x, event.button.y, inputData, true);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    inputData = ProcessMouseLeftClick(event.button.x, event.button.y, inputData, false);
                }
                break;
            default:
                break;
        }
        if(inputData.Quit) {
            break;
        }
    }
}

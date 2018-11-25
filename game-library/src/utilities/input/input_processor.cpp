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
        case SDLK_RETURN:
            inputData.Action1 = keyDown;
            break;
        default:
            break;
    }
    return inputData;
}

InputData InputProcessor::ProcessMouseLeftClick(int32_t x, int32_t y, InputData inputData, bool pressed) {
    inputData.LeftClick.Location.x = x;
    inputData.LeftClick.Location.y = y;
    inputData.LeftClick.Clicked = pressed;
    return inputData;
}

InputData InputProcessor::ProcessControllerButtonEvent(uint8_t button, InputData inputData, bool pressed) {
    switch(button) {
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            inputData.MoveUp = pressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            inputData.MoveDown = pressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            inputData.MoveLeft = pressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            inputData.MoveRight = pressed;
            break;
        case SDL_CONTROLLER_BUTTON_A:
            inputData.Action1 = pressed;
            break;
        case SDL_CONTROLLER_BUTTON_BACK:
            inputData.Quit = pressed;
            break;
    }
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
            case SDL_KEYUP:
                inputData = ProcessKeyEvent(event.key.keysym.sym, inputData, event.key.state == SDL_PRESSED);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    inputData = ProcessMouseLeftClick(event.button.x, event.button.y, inputData, event.button.state == SDL_PRESSED);
                }
                break;
            case SDL_MOUSEMOTION:
                inputData.MouseLocation.x = event.motion.x;
                inputData.MouseLocation.y = event.motion.y;
                break;
            //case SDL_CONTROLLERDEVICEADDED:
            //    controllers.emplace_back(SDL_GameControllerOpen(event.cdevice.which));
            //    break;
            //case SDL_CONTROLLERDEVICEREMOVED:
            //    break;
            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
                inputData = ProcessControllerButtonEvent(event.cbutton.button, inputData, event.cbutton.state == SDL_PRESSED);
                break;
            /*case SDL_JOYAXISMOTION:
                inputData = ProcessControllerAxisEvent(event.jaxis.axis, inputData, event.jaxis.value);
                break;*/
            default:
                break;
        }
        if(inputData.Quit) {
            break;
        }
    }
}

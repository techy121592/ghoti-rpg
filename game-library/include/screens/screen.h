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

#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "utilities/input/input-data.h"
#include "components/primitive-components/component.h"
#include "components/primitive-components/drawable-component.h"
#include "components/drawable-components/button.h"

/*
 * Notes:
 * Any screens implementing this class needs to set doneLoading once done loading resources.
 * Otherwise, you will be stuck on the load screen
 */

class Screen {
protected:
    std::vector<Component*> components = {};
    std::vector<Button*> buttonComponents = {};
    std::vector<DrawableComponent*> drawableComponents = {};
    Screen* nextScreen = nullptr;
public:
    Screen();

    virtual ~Screen() {
        for(Component* component : components) {
            delete component;
        }
        components.clear();
    };

    virtual void Update(uint32_t deltaTime, InputData inputData) {
        for(auto button : buttonComponents) {
            if(inputData.LeftClick.Clicked) {
                if(button->WithinButton(inputData.LeftClick.Location)) {
                    button->Click();
                    break;
                }
            }
            if(button->WithinButton(inputData.MouseLocation)) {
                button->Select();
                for(auto otherButton: buttonComponents) {
                    if(button != otherButton) {
                        otherButton->Unselect();
                    }
                }
            }
        }
        if(inputData.Quit) {
            nextScreen = nullptr;
        }
    };

    Screen* NextScreen();
    bool IsReady();
    std::vector<DrawableComponent*> CloneDrawables();
    void AddComponent(Component* component);
};

#endif

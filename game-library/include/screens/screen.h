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

#ifndef SCREEN_H
#define SCREEN_H

#include <list>
#include <iostream>
#include <SDL.h>
#include "utilities/input/input_data.h"
#include "components/primitive-components/component.h"
#include "components/primitive-components/drawable_component.h"
#include "components/drawable-components/button.h"

/*
 * Notes:
 * Any screens implementing this class needs to set doneLoading once done loading resources.
 * Otherwise, you will be stuck on the load screen
 */

class Screen {
protected:
    std::list<Component*> components = {};
    std::list<Button*> clickableComponents = {};
    std::list<DrawableComponent*> drawableComponents = {};
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
        if(inputData.LeftClick.Clicked) {
            for(auto clickableComponent : clickableComponents) {
                if(clickableComponent->WithinButton(inputData.LeftClick.X, inputData.LeftClick.Y)) {
                    clickableComponent->Click();
                }
            }
        }
        if(inputData.Quit) {
            nextScreen = nullptr;
        }
    };

    Screen* NextScreen();
    bool IsReady();
    std::list<DrawableComponent*> CloneDrawables();
    void AddComponent(Component* component);
};

#endif

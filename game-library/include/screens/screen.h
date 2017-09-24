/**
 * Copyright (C) 2017  David Welch & Ankit Singhania
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

class Screen {
protected:
    std::list<Component*> components = {}; // Should probably make some other type to hold on, but for now this is good enough
    Screen* nextScreen = nullptr;
public:
    Screen();
    virtual ~Screen() {
        for(Component* component : components) {
            delete component;
        }
        components.clear();
    };
    virtual void Setup() = 0;
    virtual void Update(uint32_t deltaTime, InputData inputData) = 0;
    virtual bool CheckSetup() = 0;

    Screen* NextScreen();
    std::list<DrawableComponent*> CloneDrawables();
};

#endif

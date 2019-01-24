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

#include "screens/screen.h"

Screen::Screen() {
    nextScreen = this;
}

Screen* Screen::NextScreen() {
    return nextScreen;
}

bool Screen::IsReady() {
    for(auto component : components) {
        if(!component->IsReady()) {
            return false;
        }
    }
    return true;
}

std::list<DrawableComponent*> Screen::CloneDrawables() {
    std::list<DrawableComponent*> tempListOfDrawableComponents = {};
    for(auto drawableComponent : drawableComponents) {
        tempListOfDrawableComponents.emplace_back(drawableComponent->Clone());
    }
    return tempListOfDrawableComponents;
}

void Screen::AddComponent(Component* component) {
    components.emplace_back(component);
    auto drawableComponent = dynamic_cast<DrawableComponent*>(component);
    if(drawableComponent != nullptr) {
        drawableComponents.emplace_back(drawableComponent);
    }
    auto buttonComponent = dynamic_cast<Button*>(component);
    if(buttonComponent != nullptr) {
        buttonComponents.emplace_back(buttonComponent);
    }
}

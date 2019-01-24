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

#include "components/drawable-components/button.h"

Button::Button(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t defaultFrame, uint32_t selectedFrame, const std::string path,
               const std::function<void()> onClick)
        : DrawableComponent(x, y, width, height, defaultFrame, path) {
    this->defaultFrame = defaultFrame;
    this->selectedFrame = selectedFrame;
    this->onClick = onClick;
}

void Button::Click() {
    onClick();
}

void Button::Select() {
    if(!selected) {
        selected = true;
        SetFrame(selectedFrame);
    }
}

void Button::Unselect() {
    if(selected) {
        selected = false;
        SetFrame(defaultFrame);
    }
}

bool Button::WithinButton(SDL_Point point) {
    return point.x >= locationRectangle.x && point.x <= locationRectangle.x + locationRectangle.w &&
            point.y >= locationRectangle.y && point.y <= locationRectangle.y + locationRectangle.h;
}

void Button::SetButtonRelationship(Button* button, ButtonRelationship relationship, bool propagate) {
    switch(relationship) {
        case ButtonRelationship::Below:
            buttonBelow = button;
            break;
        case ButtonRelationship::Above:
            buttonAbove = button;
            break;
        case ButtonRelationship::Left:
            buttonLeft = button;
            break;
        case ButtonRelationship::Right:
            buttonRight = button;
            break;
    }
    if(propagate) {
        button->SetButtonRelationship(this, static_cast<ButtonRelationship>(relationship * -1), false);
    }
}

bool Button::IsSelected() {
    return selected;
}

void Button::ProcessInput(InputData inputData) {
    if(inputData.Action1) {
        return Click();
    }

    Button* newSelectedButton = inputData.MoveUp && buttonAbove != nullptr ? buttonAbove :
                                inputData.MoveDown && buttonBelow != nullptr ? buttonBelow :
                                inputData.MoveLeft && buttonLeft != nullptr ? buttonLeft :
                                inputData.MoveRight && buttonRight != nullptr ? buttonRight :
                                nullptr;

    if(newSelectedButton != nullptr) {
        this->Unselect();
        newSelectedButton->Select();
    }
}

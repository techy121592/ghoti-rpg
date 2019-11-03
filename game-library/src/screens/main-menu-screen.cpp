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

#include "screens/main-menu-screen.h"

MainMenuScreen::MainMenuScreen() {
    auto mainMenuSettings = ResourceLoader::LoadMainMenuSettings();
    auto buttonSettingsVector = mainMenuSettings.GetButtonSettings();
    std::map<std::string, Button*> buttonMap;

    for (auto buttonSettings : buttonSettingsVector) {
        auto buttonType = buttonSettings.GetButtonType();
        std::function<void()> onClick = nullptr;

        if (buttonType == ButtonType::LoadMap) {
            onClick = [this]() {
                nextScreen = new LoadScreen<GameScreen>();
            };
        } else if (buttonType == ButtonType::ExitGame) {
            onClick = [this](){
                nextScreen = nullptr;
            };
        }

        auto button = new Button(buttonSettings.GetX(), buttonSettings.GetY(), buttonSettings.GetWidth(), buttonSettings.GetHeight(), buttonSettings.GetDefaultFrame(), buttonSettings.GetSelectedFrame(), buttonSettings.GetImagePath(), onClick);
        buttonMap.emplace(buttonSettings.GetName(), button);

        if (!buttonSettings.GetAbove().empty()) {
            button->SetButtonRelationship(buttonMap.at(buttonSettings.GetAbove()), ButtonRelationship::Below);
        }
        if (!buttonSettings.GetBelow().empty()) {
            button->SetButtonRelationship(buttonMap.at(buttonSettings.GetBelow()), ButtonRelationship::Above);
        }
        if (!buttonSettings.GetLeft().empty()) {
            button->SetButtonRelationship(buttonMap.at(buttonSettings.GetLeft()), ButtonRelationship::Left);
        }
        if (!buttonSettings.GetRight().empty()) {
            button->SetButtonRelationship(buttonMap.at(buttonSettings.GetRight()), ButtonRelationship::Right);
        }
        AddComponent(button);
        if (buttonSettings.IsDefault()) {
            defaultButton = button;
        }
    }
}

void MainMenuScreen::Update(uint32_t deltaTime, InputData inputData) {
    if(!defaultButtonSelected) {
        defaultButton->Select();
        defaultButtonSelected = true;
    }
    Screen::Update(deltaTime, inputData);
    for(auto button : buttonComponents) {
        if(button->IsSelected()) {
            button->ProcessInput(inputData);
            break;
        }
    }
}
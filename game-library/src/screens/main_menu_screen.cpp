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

#include "screens/main_menu_screen.h"

MainMenuScreen::MainMenuScreen() {
    startButton = new Button(100,  100, 200, 75, 0, "start_button.png",
        [this]() {
            this->nextScreen = new LoadScreen<GameScreen>();
        });
    exitButton = new Button(100, 200, 200, 75, 0, "exit_button.png",
        [this](){
            nextScreen = nullptr;
        });
    components.emplace_back(startButton);
    components.emplace_back(exitButton);
}

void MainMenuScreen::Update(uint32_t deltaTime, InputData inputData) {
    std::cout << "MainMenuScreen" << std::endl;
    if(inputData.MoveUp) {
        startButton->Click();
    } else if(inputData.MoveDown) {
        exitButton->Click();
    } else if(inputData.Quit) {
        nextScreen = nullptr;
    }
}
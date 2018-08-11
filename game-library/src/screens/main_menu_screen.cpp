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

Button* startButton = nullptr;

MainMenuScreen::MainMenuScreen() {
    //startButton = new Button(100,  100, 200, 75, 0, ResourceLoader::LoadImage("start_button.png"),
    //    [this]() {
    //        std::cout << "Start button clicked" << std::endl;
            this->nextScreen = new LoadScreen<GameScreen>();
    //        std::cout << "Start button click end" << std::endl;
    //    });
    //components.emplace_back(startButton);
    //components.emplace_back(new Button(100, 200, 200, 75, 0, ResourceLoader::LoadImage("start_button.png"),
    //    [this](){
    //        std::cout << "Exit button clicked" << std::endl;
    //        nextScreen = nullptr;
    //        std::cout << "Exit button click end" << std::endl;
    //    }));
    //std::cout << "Button creation end" << std::endl;
}

void MainMenuScreen::Update(uint32_t deltaTime, InputData inputData) {
    std::cout << "MainMenuScreen" << std::endl;
    if(inputData.MoveUp) {
        startButton->Click();
    } else if(inputData.Quit) {
        nextScreen = nullptr;
    }
}
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

#include "screens/game_screen.h"

GameScreen::GameScreen(SDL_Renderer* ren) {
    auto tileMap = ResourceLoader::LoadMap("test.tmx", ren);
    components.push_back(tileMap);
    components.push_back(tileMap->GetBottomLayer());
    components.push_back(new Character(16, 16, 16, 16, 0, ResourceLoader::LoadImage("character_placeholder.png", ren), 0.075));
    components.push_back(tileMap->GetTopLayer());
}

GameScreen::~GameScreen() = default;

void GameScreen::Setup() {
}

bool GameScreen::CheckSetup() {
    std::cout << "Checking GameScreen setup status" << std::endl;
    return components.size() == 4;
}

void GameScreen::Update(uint32_t deltaTime, InputData inputData) {
    if (inputData.Quit) {
        std::cout << "Setting nextScreen to nullptr" << std::endl;
        nextScreen = nullptr;
    }

    for(auto component : components) {
        auto character = dynamic_cast<Character*>(component);
        if(character != nullptr) {
            character->Update(deltaTime, inputData);
        }
    }
}

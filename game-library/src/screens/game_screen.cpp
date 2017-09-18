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
    components.push_back(ResourceLoader::LoadMap("test.tmx", ren));
}

GameScreen::~GameScreen() {
    SDL_DestroyTexture(tileSetTexture);
}

void GameScreen::Setup() {
}

bool GameScreen::CheckSetup() {
    return tileSetTexture != nullptr;
}

void GameScreen::Update(uint32_t deltaTime, InputData inputData) {
    if (inputData.Quit) {
        nextScreen = nullptr;
    }
    std::cout << deltaTime << std::endl;
}

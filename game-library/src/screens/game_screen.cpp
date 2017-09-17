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
    tileSetTexture = ResourceLoader::LoadImage("test_tileset.png", ren);
}

GameScreen::~GameScreen() {
    SDL_DestroyTexture(tileSetTexture);
}

void GameScreen::Setup() {
    auto tileSet = new TileSet(16, 16, tileSetTexture); // Need to add properties, for example, damage: 1, location: reset, etc.
    components.push_back(tileSet->CreateTile(0, 0, 0)); // This will be done by the resource loader rather than in the screen code, but I am just trying to put together the basics that work
    components.push_back(tileSet->CreateTile(0, 1, 1));
    components.push_back(tileSet->CreateTile(0, 2, 2));
    components.push_back(tileSet->CreateTile(0, 3, 3));
    // Tiles should be stored in a tilemap so that it can be pre-rendered.
    // Which means this code will probably have to be moved up to the constructor
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

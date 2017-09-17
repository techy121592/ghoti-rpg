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
    auto tileSet = new TileSet(16, 16, tileSetTexture); // Need to add properties, for example, damage: 1, location: reset, etc.
    std::list<Tile*> tiles;
    tiles.push_back(tileSet->CreateTile(0, 0, 0));
    tiles.push_back(tileSet->CreateTile(0, 1, 1));
    tiles.push_back(tileSet->CreateTile(0, 2, 2));
    tiles.push_back(tileSet->CreateTile(0, 3, 3));
    components.push_back(new TileMap(4, 1, 16, 16, tiles, ren));
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

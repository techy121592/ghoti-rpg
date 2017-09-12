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
    helloTexture = ResourceLoader::LoadImage("test_tileset.png", ren);
    SDL_Rect sourceRect;
    sourceRect.h = 16;
    sourceRect.w = 16;
    sourceRect.x = 0;
    sourceRect.y = 0;
    SDL_Rect destRect;
    destRect.h = 16;
    destRect.w = 16;
    destRect.x = 0;
    destRect.y = 0;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 16;
    destRect.y = 0;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 32;
    destRect.y = 0;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 0;
    destRect.y = 16;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 16;
    destRect.y = 16;
    sourceRect.x = 16;
    sourceRect.y = 0;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 32;
    destRect.y = 16;
    sourceRect.x = 0;
    sourceRect.y = 0;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 0;
    destRect.y = 32;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 16;
    destRect.y = 32;
    sourceRect.x = 0;
    sourceRect.y = 16;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
    destRect.x = 32;
    destRect.y = 32;
    sourceRect.x = 16;
    sourceRect.y = 16;
    components.push_back(new DrawableComponent(destRect, sourceRect, helloTexture));
}

GameScreen::~GameScreen() {
    SDL_DestroyTexture(helloTexture);
}

bool GameScreen::CheckSetup() {
    return helloTexture != nullptr;
}

void GameScreen::Update(uint32_t deltaTime, InputData inputData) {
    if (inputData.Quit) {
        nextScreen = nullptr;
    }
}

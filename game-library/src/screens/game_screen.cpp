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

#include "screens/game_screen.h"

GameScreen::GameScreen() {
    tileMap = ResourceLoader::LoadMap("test.tmx");
    character = new Character(23, 23, 14, 14, 0, "character_placeholder.png", 0.075);

    AddComponent(tileMap);
    AddComponent(tileMap->GetBottomLayer());
    AddComponent(character);
    AddComponent(tileMap->GetTopLayer());
}

void GameScreen::Update(uint32_t deltaTime, InputData inputData) {
    Screen::Update(deltaTime, inputData);
    character->SetInput(inputData);
    character->Update(deltaTime, tileMap);
}

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

#include "screens/hello_screen.h"

HelloScreen::HelloScreen(SDL_Renderer* ren) {
    helloTexture = ResourceLoader::LoadImage("hello.bmp", ren);
    components.push_back(new DrawableComponent(0, 0, 640, 480, 0, helloTexture));
}

HelloScreen::~HelloScreen() {
    SDL_DestroyTexture(helloTexture);
}

bool HelloScreen::CheckSetup() {
    return helloTexture != nullptr;
}

void HelloScreen::Update(const uint32_t deltaTime, const InputData inputData) {
    if (inputData.Quit) {
        nextScreen = nullptr;
    }
}

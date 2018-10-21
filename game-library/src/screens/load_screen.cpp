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

#include "screens/load_screen.h"

template <class T>
LoadScreen<T>::LoadScreen() {
    AddComponent(new DrawableComponent(0, 0, 640, 480, 0, "loading.png"));

    ThreadPool::AddTask([this](){
        nextScreen = new T();
    }, false);
}

template<class T>
void LoadScreen<T>::Update(uint32_t deltaTime, InputData inputData) {
    Screen::Update(deltaTime, inputData);
}

template class LoadScreen<HelloScreen>;
template class LoadScreen<GameScreen>;
template class LoadScreen<MainMenuScreen>;

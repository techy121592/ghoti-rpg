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

template<class T> bool LoadScreen<T>::doneLoading = false;
template<class T> Screen* LoadScreen<T>::nextScreenHolder = nullptr;

template <class T>
void LoadScreen<T>::Setup(SDL_Renderer* ren) {
    nextScreenHolder = new T();
    components.emplace_back(new DrawableComponent(0, 0, 640, 480, 0, ResourceLoader::LoadImage("loading.png", ren)));
    ThreadPool::AddTask([ren](){
        nextScreenHolder->Setup(ren);
        doneLoading = true;
    }, false);
}

template<class T>
bool LoadScreen<T>::CheckSetup() {
    return components.size() == 1;
}

template<class T>
void LoadScreen<T>::Update(uint32_t deltaTime, InputData inputData) {
    if(doneLoading) {
        nextScreen = nextScreenHolder;
        nextScreenHolder = nullptr;
        doneLoading = false;
    } else if(inputData.Quit) {
        nextScreen = nullptr;
    }
}

template class LoadScreen<HelloScreen>;
template class LoadScreen<GameScreen>;
template class LoadScreen<MainMenuScreen>;

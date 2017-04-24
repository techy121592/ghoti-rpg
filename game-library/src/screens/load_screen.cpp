#include "screens/load_screen.h"
#include <iostream>

template<class T> bool LoadScreen<T>::doneLoading = false;
template<class T> Screen* LoadScreen<T>::nextScreenHolder = nullptr;

template<class T>
LoadScreen<T>::LoadScreen(SDL_Renderer* ren) {
    loadingTexture = ResourceLoader::LoadImage("loading.png", ren);
    components.push_back(new DrawableComponent(0, 0, 640, 480, 0, loadingTexture));

    ThreadPool::AddTask([ren]{
        nextScreenHolder = new T(ren);
        doneLoading = true;
    }, false);
}

template<class T>
LoadScreen<T>::~LoadScreen() {
    SDL_DestroyTexture(loadingTexture);
}

template<class T>
bool LoadScreen<T>::CheckSetup() {
    if(loadingTexture == nullptr) {
        return false;
    }
    return true;
}

template<class T>
void LoadScreen<T>::Update(const uint32_t deltaTime, const InputData inputData) {
    if(doneLoading) {
        nextScreen = nextScreenHolder;
        nextScreenHolder = nullptr;
        doneLoading = false;
    }
}

template class LoadScreen<HelloScreen>;

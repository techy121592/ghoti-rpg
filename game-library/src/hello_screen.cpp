#include "hello_screen.h"

HelloScreen::HelloScreen(SDL_Renderer* ren) {
    components.push_back(new DrawableComponent(0, 0, 640, 480, 0, ResourceLoader::LoadImage("hello.bmp", ren)));
}

HelloScreen::~HelloScreen() {
    for(DrawableComponent* component : components) {
        delete component;
    }
}

bool HelloScreen::CheckSetup() {
    return true;
}

Screen* HelloScreen::Update(const uint32_t deltaTime, InputData* inputData) {
    if (inputData != nullptr && inputData->Quit) {
        return nullptr;
    }
    return this;
}

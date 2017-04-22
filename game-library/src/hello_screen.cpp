#include "hello_screen.h"

HelloScreen::HelloScreen(SDL_Renderer* ren) {
    SDL_Texture* helloTexture = ResourceLoader::LoadImage("hello.bmp", ren);
    components.push_back(new DrawableComponent(0, 0, 640, 480, 0, helloTexture));
}

HelloScreen::~HelloScreen() {
    for(DrawableComponent* component : components) {
        delete component;
    }
}

bool HelloScreen::CheckSetup() {
    return true;
}

void HelloScreen::Update(const uint32_t deltaTime, const InputData inputData) {
    if (inputData.Quit) {
        nextScreen = nullptr;
    }
}

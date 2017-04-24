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
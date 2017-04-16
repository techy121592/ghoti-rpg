#include "hello_screen.h"

HelloScreen::HelloScreen(SDL_Renderer* ren) {
    helloTexture = ResourceLoader::LoadImage("hello.bmp", ren);
}

HelloScreen::~HelloScreen() {
    if (helloTexture != nullptr) {
        SDL_DestroyTexture(helloTexture);
    }
}

bool HelloScreen::CheckSetup() {
    return helloTexture != nullptr;
}

void HelloScreen::RenderComponents(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, helloTexture, NULL, NULL);
}

Screen* HelloScreen::Update(const uint32_t deltaTime, InputData* inputData) {
    if (inputData->Quit) {
        return nullptr;
    }
    return this;
}

#include "hello_screen.h"

HelloScreen::HelloScreen(SDL_Renderer* ren) {
    helloTexture = ResourceLoader::LoadImage("hello.bmp", ren);
}

HelloScreen::~HelloScreen() {
    if (helloTexture != nullptr) {
        SDL_DestroyTexture(helloTexture);
    }
}

void HelloScreen::Render(SDL_Renderer* ren) {
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, helloTexture, NULL, NULL);
    SDL_RenderPresent(ren);
}

Screen* HelloScreen::Update(const uint32_t deltaTime, InputData* inputData) {
    if (inputData->Quit) {
        return nullptr;
    }
    return this;
}

int HelloScreen::CheckSetup() {
    if (helloTexture == nullptr) {
        return 1;
    }
    return 0;
}

#include "screens/game_screen.h"

GameScreen::GameScreen(SDL_Renderer* ren) {
    helloTexture = ResourceLoader::LoadImage("hello.bmp", ren);
    components.push_back(new DrawableComponent(0, 0, 640, 480, 0, helloTexture));
}

GameScreen::~GameScreen() {
    SDL_DestroyTexture(helloTexture);
}

bool GameScreen::CheckSetup() {
    return helloTexture != nullptr;
}

void GameScreen::Update(uint32_t deltaTime, InputData inputData) {
    if (inputData.Quit) {
        nextScreen = nullptr;
    }
}

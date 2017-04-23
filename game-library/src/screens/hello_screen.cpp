#include "screens/hello_screen.h"

HelloScreen::HelloScreen(SDL_Renderer* ren) {
    std::cout << "Loading hello.bmp" << std::endl;
    helloTexture = ResourceLoader::LoadImage("hello.bmp", ren);
    components.push_back(new DrawableComponent(0, 0, 640, 480, 0, helloTexture));
}

HelloScreen::~HelloScreen() {
    std::cout << "Unloading HelloScreen" << std::endl;
    SDL_DestroyTexture(helloTexture);
}

bool HelloScreen::CheckSetup() {
    if(helloTexture == nullptr) {
        std::cout << "Failed to setup HelloScreen" << std::endl;
        return false;
    }
    return true;
}

void HelloScreen::Update(const uint32_t deltaTime, const InputData inputData) {
    if (inputData.Quit) {
        nextScreen = nullptr;
    }
}

void HelloScreen::MainThreadActivity() {

}

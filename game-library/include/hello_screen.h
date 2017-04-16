#ifndef HELLO_SCREEN_H
#define HELLO_SCREEN_H

#include <SDL.h>
#include "resource_loader.h"
#include "screen.h"

class HelloScreen : public Screen {
    SDL_Texture* helloTexture;
public:
    HelloScreen(SDL_Renderer* ren);
    ~HelloScreen();
    Screen* Update(const uint32_t deltaTime, InputData* inputData);
    void RenderComponents(SDL_Renderer* ren);
    bool CheckSetup();
};

#endif

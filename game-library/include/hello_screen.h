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
    bool CheckSetup();
    void RenderComponents(SDL_Renderer* ren);
    Screen* Update(const uint32_t deltaTime, InputData* inputData);
};

#endif

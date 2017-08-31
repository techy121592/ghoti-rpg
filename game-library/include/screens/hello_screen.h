#ifndef HELLO_SCREEN_H
#define HELLO_SCREEN_H

#include <SDL.h>
#include "utilities/resource_loader.h"
#include "screen.h"

class HelloScreen : public Screen {
private:
    SDL_Texture* helloTexture;
public:
    HelloScreen(SDL_Renderer* ren);
    ~HelloScreen();
    bool CheckSetup();
    void Update(const uint32_t deltaTime, const InputData inputData);
};

#endif

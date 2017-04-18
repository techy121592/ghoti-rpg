#ifndef HELLO_SCREEN_H
#define HELLO_SCREEN_H

#include <iostream>
#include <SDL.h>
#include "resource_loader.h"
#include "screen.h"

class HelloScreen : public Screen {
public:
    HelloScreen(SDL_Renderer* ren);
    ~HelloScreen();
    bool CheckSetup();
    Screen* Update(const uint32_t deltaTime, InputData* inputData);
};

#endif

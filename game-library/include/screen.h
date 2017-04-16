#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "input_data.h"

class Screen {
public:
    void RenderScreen(SDL_Renderer* ren);

    virtual ~Screen() {};
    virtual Screen* Update(const uint32_t deltaTime, InputData* inputData) = 0;
    virtual void RenderComponents(SDL_Renderer* ren) = 0;
    virtual bool CheckSetup() = 0;
};

#endif

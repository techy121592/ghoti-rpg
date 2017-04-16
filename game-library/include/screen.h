#ifndef SCREEN_H
#define SCREEN_H

#include "input_data.h"

class Screen {
public:
    virtual ~Screen() {};
    virtual Screen* Update(const uint32_t deltaTime, InputData* inputData) = 0;
    virtual void Render(SDL_Renderer* ren) = 0;
    virtual bool CheckSetup() = 0;
};

#endif
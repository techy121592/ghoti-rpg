#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SDL.h>
#include "utilities/resource_loader.h"
#include "screen.h"

class GameScreen : public Screen {
private:
    SDL_Texture* helloTexture;
public:
    explicit GameScreen(SDL_Renderer* ren);
    ~GameScreen();
    bool CheckSetup();
    void Update(uint32_t deltaTime, InputData inputData);
};

#endif

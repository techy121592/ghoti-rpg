#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <tuple>
#include <SDL.h>

#include "resource_loader.h"
#include "input_data.h"
#include "screen.h"
#include "hello_screen.h"

class Game {
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    Screen* screen = nullptr;
    uint32_t fps;

    std::tuple<SDL_Window*, SDL_Renderer*> SetupSDL(const uint32_t width, const uint32_t height);
    bool GameLoop(SDL_Renderer* ren, Screen*& screen, const uint32_t maxFPS);
    InputData GetInput();
    void CloseSDL(SDL_Window*& win, SDL_Renderer*& ren, Screen*& screen);
    void PauseForRestOfFrame(const int32_t targetFrameLength, const int32_t deltaTime);

public:
    Game(const uint32_t width, const uint32_t height, const uint32_t maxFPS);
    int Run();
    bool CheckSetup();
};

#endif

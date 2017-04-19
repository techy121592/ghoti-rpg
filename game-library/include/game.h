#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <tuple>
#include <thread>
#include <list>
#include <SDL.h>
#include "resource_loader.h"
#include "input_data.h"
#include "screen.h"
#include "hello_screen.h"
#include "input_processor.h"
#include "drawable_component.h"

class Game {
private:
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    static Screen* screen;
    uint32_t fps;
    std::thread threads[2];
    InputData inputData;

    std::tuple<SDL_Window*, SDL_Renderer*> SetupSDL(const uint32_t width, const uint32_t height);
    void CloseSDL(SDL_Window*& win, SDL_Renderer*& ren, Screen*& screen);
    void PauseForRestOfFrame(const int32_t targetFrameLength, const int32_t deltaTime);
    bool Step(const int32_t deltaTime);
    static void UpdateAndSetScreen(const int deltaTime, InputData* input);
    static void DrawComponents(SDL_Renderer* ren, std::list<DrawableComponent*> drawableComponents);
    bool GameLoop();

public:
    Game(const uint32_t width, const uint32_t height, const uint32_t maxFPS);
    bool CheckSetup();
    int Run();
};

#endif

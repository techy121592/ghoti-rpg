#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <tuple>
#include <list>
#include <SDL.h>
#include "resource_loader.h"
#include "input_data.h"
#include "input_processor.h"
#include "thread_pool.h"
#include "components/drawable_component.h"
#include "screens/screen.h"
#include "screens/hello_screen.h"

class Game {
private:
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    static Screen* screen;
    uint32_t fps;

    std::tuple<SDL_Window*, SDL_Renderer*> SetupSDL(const uint32_t width, const uint32_t height);
    void CloseSDL(SDL_Window*& win, SDL_Renderer*& ren, Screen*& screen);
    void PauseForRestOfFrame(const int32_t targetFrameLength, const int32_t deltaTime);
    void FireOffThreadsToUpdateAndGetInput(Screen* screenPointer, const uint32_t deltaTime, const InputData inputData);
    void Draw(std::list<DrawableComponent*> drawableComponentsData);
    bool Step(const int32_t deltaTime);
    bool GameLoop();
public:
    Game(const uint32_t width, const uint32_t height, const uint32_t maxFPS);
    ~Game();
    bool CheckSetup();
    int Run();
};

#endif

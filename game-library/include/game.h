#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <tuple>
#include <SDL.h>

#include "resource_loader.h"
#include "input_data.h"

class Game {
    bool running;

    std::tuple<SDL_Window*, SDL_Renderer*> setupSDL(const uint32_t width, const uint32_t height);
    SDL_Texture* loadImage(const std::string &fileName, SDL_Renderer* ren);
    int gameLoop(SDL_Renderer* ren, SDL_Texture* tex, const uint32_t maxFPS);
    InputData getInput();
    void update(const uint32_t deltaTime, InputData* inputData);
    void render(SDL_Renderer* ren, SDL_Texture* tex);
    void closeSDL(SDL_Window*& win, SDL_Renderer*& ren, SDL_Texture*& tex);

public:
    int run(const uint32_t width, const uint32_t height, const uint32_t maxFPS);
};

#endif

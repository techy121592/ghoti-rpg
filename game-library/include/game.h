#ifndef GAME_H
#define GAME_H

#include <string>
#include <tuple>
#include <SDL.h>
#include <SDL_image.h>
#include "input-data.h"

class Game {
    bool running;

    std::tuple<SDL_Window*, SDL_Renderer*, const int> setupSDL(const uint32_t width, const uint32_t height);
    std::tuple<SDL_Texture*, const int> loadImage(const std::string &fileName, SDL_Renderer* ren);
    int gameLoop(SDL_Renderer* ren, SDL_Texture* tex, const uint32_t maxFPS);
    InputData getInput();
    void update(const uint32_t deltaTime, InputData* inputData);
    void render(SDL_Renderer* ren, SDL_Texture* tex);
    void closeSDL(SDL_Window*& win, SDL_Renderer*& ren, SDL_Texture*& tex);
public:
    int run(const uint32_t width, const uint32_t height, const uint32_t maxFPS);
};

#endif

#ifndef GAME_H
#define GAME_H

#include <string>
#include <tuple>
#include <SDL.h>
#include <SDL_image.h>
#include "input-data.h"

class Game {
    bool running;

    std::tuple<SDL_Window*, SDL_Renderer*, int> setupSDL();
    std::tuple<SDL_Texture*, int> loadImage(const std::string &fileName, SDL_Renderer* ren);
    int gameLoop(SDL_Renderer* ren, SDL_Texture* tex);
    InputData getInput();
    void update(uint32_t deltaTime, InputData* inputData);
    void render(SDL_Renderer* ren, SDL_Texture* tex);
    void closeSDL(SDL_Window*& win, SDL_Renderer*& ren, SDL_Texture*& tex);
public:
    int run();
};

#endif

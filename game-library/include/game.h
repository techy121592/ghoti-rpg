#ifndef GAME_H
#define GAME_H

#include <string>
#include <SDL.h>
#include "input-data.h"

class Game {
    bool running;

    int setupSDL(SDL_Window*& win, SDL_Renderer*& ren);
    int loadImage(std::string fileName, SDL_Renderer* ren, SDL_Texture*& tex);
    int gameLoop(SDL_Renderer*& ren, SDL_Texture*& tex);
    InputData getInput();
    void update(uint32_t deltaTime, InputData* inputData);
    void render(SDL_Renderer*& ren, SDL_Texture*& tex);
    void closeSDL(SDL_Window*& win, SDL_Renderer*& ren, SDL_Texture*& tex);
public:
    int run();
};

#endif

#include "game.h"

#include <iostream>
#include "res_path.h"

int Game::setupSDL(SDL_Window*& win, SDL_Renderer*& ren) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    return 0;
}

int Game::loadImage(const std::string &fileName, SDL_Renderer* ren, SDL_Texture*& tex) {
    const std::string imagePath = getResourcePath("images") + fileName;
    tex = IMG_LoadTexture(ren, imagePath.c_str());
    if (tex == nullptr) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

InputData Game::getInput() {
    SDL_Event events;
    InputData inputData;

    while(SDL_PollEvent(&events)) {
        // This is where we get input
        if(events.type == SDL_QUIT) {
            inputData.Quit = true;
        }
    }

    return inputData;
}

void Game::update(uint32_t deltaTime, InputData* inputData) {
    if(inputData->Quit) {
        running = false;
    }

    // This is where I go through all of the game objects and update them
    // Player character and controls will have to be passed events/input here
}

void Game::render(SDL_Renderer*& ren, SDL_Texture*& tex) {
    SDL_RenderClear(ren);
    // Should take a list of drawable things and draw them at their destination
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
}

int Game::gameLoop(SDL_Renderer*& ren, SDL_Texture*& tex) {
    uint32_t maxFPS = 60;
    uint32_t previousTime, currentTime, deltaTime;

    currentTime = SDL_GetTicks();
    running = true;

    while(running) {
        previousTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - previousTime;

        InputData input = getInput();
        update(deltaTime, &input);
        render(ren, tex);

        int64_t targetFrameLength = (int64_t)(1000 / maxFPS);
        int64_t delay = targetFrameLength - deltaTime;
        uint32_t fps = delay >= 0 ? 60 : 1000 / (targetFrameLength - delay);

        // Should print this in-game
        std::cout << "FPS: " << fps << std::endl;

        if(delay > 0) {
            SDL_Delay((uint32_t)delay);
        }
    }
    return 0;
}

void Game::closeSDL(SDL_Window*& win, SDL_Renderer*& ren, SDL_Texture*& tex) {
    if(tex != nullptr) {
        SDL_DestroyTexture(tex);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int Game::run() {
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;

    if (setupSDL(win, ren)) {
        return 1;
    }

    std::cout << "Resource path is: " << getResourcePath() << std::endl;
    SDL_Texture *tex = nullptr;
    if (loadImage("hello.bmp", ren, tex)) {
        closeSDL(win, ren, tex);
        return 1;
    }

    if (gameLoop(ren, tex)) {
        std::cout << "Game loop failed!" << std::endl;
        return 1;
    }

    closeSDL(win, ren, tex);
    std::cout << "Game completed successfully" << std::endl;
    return 0;
}

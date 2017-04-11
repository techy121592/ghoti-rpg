#include "game.h"

#include <iostream>
#include "res_path.h"

std::tuple<SDL_Window*, SDL_Renderer*, int> Game::setupSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return std::make_tuple(nullptr, nullptr, 1);
    }

    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return std::make_tuple(nullptr, nullptr, 1);
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return std::make_tuple(nullptr, nullptr, 1);
    }

    return std::make_tuple(win, ren, 0);
}

std::tuple<SDL_Texture*, int> Game::loadImage(const std::string &fileName, SDL_Renderer* ren) {
    const std::string imagePath = getResourcePath("images") + fileName;
    SDL_Texture* tex = IMG_LoadTexture(ren, imagePath.c_str());
    if (tex == nullptr) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return std::make_tuple(nullptr, 1);
    }

    return std::make_tuple(tex, 0);
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

void Game::render(SDL_Renderer* ren, SDL_Texture* tex) {
    SDL_RenderClear(ren);
    // Should take a list of drawable things and draw them at their destination
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
}

int Game::gameLoop(SDL_Renderer* ren, SDL_Texture* tex) {
    const uint32_t maxFPS = 60;
    const int32_t targetFrameLength = (int64_t)(1000 / maxFPS);
    uint32_t previousTime, currentTime, deltaTime;

    currentTime = SDL_GetTicks();
    running = true;

    try {
        while(running) {
            previousTime = currentTime;
            currentTime = SDL_GetTicks();
            deltaTime = currentTime - previousTime;

            InputData input = getInput();
            update(deltaTime, &input);
            render(ren, tex);

            int32_t delay = targetFrameLength - deltaTime;
            if(deltaTime > 0) {
                uint32_t fps = 1000 / deltaTime;
                std::cout << "FPS: " << fps << std::endl << "Delay: " << delay << std::endl << "Delta: " << deltaTime << std::endl << "Target: " << targetFrameLength << std::endl;
            }

            if(delay > 0) {
                // This might not be necessary, but it is more friendly.
                SDL_Delay((uint32_t)delay);
            }
        }
    } catch (const std::exception& ex) {
        return 1;
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
    std::cout << "Setting up SDL" << std::endl;
    std::tuple<SDL_Window*, SDL_Renderer*, int> windowRendererTuple = setupSDL();

    if (std::get<2>(windowRendererTuple)) {
        std::cout << "Failed to setup SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = std::get<0>(windowRendererTuple);
    SDL_Renderer *ren = std::get<1>(windowRendererTuple);

    std::cout << "Resource path is: " << getResourcePath() << std::endl;
    std::tuple<SDL_Texture*, int> textureTuple = loadImage("hello.bmp", ren);

    SDL_Texture* tex = nullptr;
    if (std::get<1>(textureTuple)) {
        std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        closeSDL(win, ren, tex);
        return 1;
    }

    tex = std::get<0>(textureTuple);

    if (gameLoop(ren, tex)) {
        std::cout << "Game loop failed!" << std::endl;
        return 1;
    }

    closeSDL(win, ren, tex);
    std::cout << "Game completed successfully" << std::endl;
    return 0;
}

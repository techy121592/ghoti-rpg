#include "game.h"

std::tuple<SDL_Window*, SDL_Renderer*> Game::setupSDL(const uint32_t width, const uint32_t height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return std::make_tuple(nullptr, nullptr);
    }

    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return std::make_tuple(nullptr, nullptr);
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return std::make_tuple(nullptr, nullptr);
    }

    return std::make_tuple(win, ren);
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

void Game::update(const uint32_t deltaTime, InputData* inputData) {
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

int Game::gameLoop(SDL_Renderer* ren, SDL_Texture* tex, const uint32_t maxFPS) {
    const int32_t targetFrameLength = (int32_t)(1000 / maxFPS);
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

            if(delay > 0) {
                // This might not be necessary since we are using delta time, but it is more friendly to share processor time.
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
    if(ren != nullptr) {
        SDL_DestroyRenderer(ren);
    }
    if(win != nullptr) {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
}

int Game::run(const uint32_t width, const uint32_t height, const uint32_t fps) {
    try {
        SDL_Window *win = nullptr;
        SDL_Renderer *ren = nullptr;
        SDL_Texture* tex = nullptr;

        std::cout << "Setting up SDL" << std::endl;
        std::tuple<SDL_Window*, SDL_Renderer*> windowRendererTuple = setupSDL(width, height);
        win = std::get<0>(windowRendererTuple);
        ren = std::get<1>(windowRendererTuple);

        if (win == nullptr || ren == nullptr) {
            std::cout << "Failed to setup SDL: " << SDL_GetError() << std::endl;
            closeSDL(win, ren, tex);
            return 1;
        }

        tex = ResourceLoader::LoadImage("hello.bmp", ren);

        if (tex == nullptr) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
            closeSDL(win, ren, tex);
            return 1;
        } else if (gameLoop(ren, tex, fps)) {
            std::cout << "Game loop failed!" << std::endl;
            closeSDL(win, ren, tex);
            return 1;
        } else {
            closeSDL(win, ren, tex);
            std::cout << "Game completed successfully" << std::endl;
            return 0;
         }
    } catch(std::exception ex) {
        return 1;
    }
}

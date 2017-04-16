#include "game.h"

Game::Game(const uint32_t width, const uint32_t height, const uint32_t fps) {
    std::cout << "Setting up SDL" << std::endl;
    std::tuple<SDL_Window*, SDL_Renderer*> windowRendererTuple = SetupSDL(width, height);
    this->win = std::get<0>(windowRendererTuple);
    this->ren = std::get<1>(windowRendererTuple);
    this->fps = fps;

    if (this->win == nullptr || this->ren == nullptr) {
        std::cout << "Failed to setup SDL: " << SDL_GetError() << std::endl;
        CloseSDL(win, ren, screen);
    }

    screen = new HelloScreen(ren);
    if(!screen->CheckSetup()) {
        std::cout << "Failed to setup the HelloScreen: " << SDL_GetError() << std::endl;
        CloseSDL(win, ren, screen);
    }
}

std::tuple<SDL_Window*, SDL_Renderer*> Game::SetupSDL(const uint32_t width, const uint32_t height) {
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

    bool Game::CheckSetup() {
    return win != nullptr && ren != nullptr;
}

InputData Game::GetInput() {
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

void Game::PauseForRestOfFrame(const int32_t targetFrameLength, const int32_t deltaTime) {
    int32_t delay = targetFrameLength - deltaTime;

    if(delay > 0) {
        // This might not be necessary since we are using delta time, but it is more friendly to share processor time.
        SDL_Delay((uint32_t)delay);
    }
}

int Game::GameLoop(SDL_Renderer* ren, Screen*& screen, const uint32_t maxFPS) {
    const int32_t targetFrameLength = (int32_t)(1000 / maxFPS);
    uint32_t previousTime, currentTime, deltaTime;
    currentTime = SDL_GetTicks();

    try {
        while(1 == 1) {
            previousTime = currentTime;
            currentTime = SDL_GetTicks();
            deltaTime = currentTime - previousTime;

            InputData input = GetInput();

            screen = screen->Update(deltaTime, &input);
            if(screen == nullptr) {
                return 0;
            }

            screen->Render(ren);

            PauseForRestOfFrame(targetFrameLength, deltaTime);
        }
    } catch (const std::exception& ex) {
        return 1;
    }

    return 0;
}

void Game::CloseSDL(SDL_Window*& win, SDL_Renderer*& ren, Screen*& screen) {
    if(screen != nullptr) {
        delete screen;
    }
    if(ren != nullptr) {
        SDL_DestroyRenderer(ren);
    }
    if(win != nullptr) {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
}

int Game::Run() {
    try {
        if (GameLoop(ren, screen, fps)) {
            std::cout << "Game loop failed!" << std::endl;
            CloseSDL(win, ren, screen);
            return 1;
        } else {
            CloseSDL(win, ren, screen);
            std::cout << "Game completed successfully" << std::endl;
            return 0;
        }
    } catch(std::exception ex) {
        return 1;
    }
}

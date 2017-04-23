#include "game.h"

Screen* Game::screen = nullptr;

Game::Game(const uint32_t width, const uint32_t height, const uint32_t fps) {
    this->fps = fps;

    std::cout << "Setting up SDL" << std::endl;
    std::tuple<SDL_Window*, SDL_Renderer*> windowRendererTuple = SetupSDL(width, height);
    this->win = std::get<0>(windowRendererTuple);
    this->ren = std::get<1>(windowRendererTuple);

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

Game::~Game() {
    std::cout << "Killing threads" << std::endl;
    ThreadPool::TerminateThreads();
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

void Game::PauseForRestOfFrame(const int32_t targetFrameLength, const int32_t deltaTime) {
    int32_t delay = targetFrameLength - deltaTime;

    std::cout << "FPS: " << 1000.0f / (deltaTime + (delay > 0 ? delay : 0)) << std::endl;

    if(delay > 0) {
        // This might not be necessary since we are using delta time, but it is more friendly to share processor time.
        SDL_Delay((uint32_t)delay);
    }
}

void Game::FireOffThreadsToUpdateAndGetInput(Screen* screenPointer, const uint32_t deltaTime, const InputData inputData) {
    ThreadPool::AddTask([screenPointer, deltaTime, inputData]() {
        screenPointer->Update(deltaTime, inputData);
    });

    ThreadPool::AddTask([]() {
        InputProcessor::GetInputFromDevice();
    });
}

void Game::Draw(std::list<DrawableComponent*> drawableComponentsData) {
    SDL_RenderClear(ren);

    for(DrawableComponent* drawableComponent : drawableComponentsData) {
        drawableComponent->Draw(ren);
    }

    SDL_RenderPresent(ren);
}

bool Game::Step(const int32_t deltaTime) {
    if(screen == nullptr) {
        return false;
    }

    std::list<DrawableComponent*> drawableComponentsData = screen->CloneDrawables();

    FireOffThreadsToUpdateAndGetInput(screen, deltaTime, InputProcessor::GetInputData());
    Draw(drawableComponentsData);

    while(ThreadPool::TasksRunning()) {
        SDL_Delay(1);
    }

    if(screen != screen->NextScreen()) {
        screen = screen->NextScreen();
    }

    return true;
}

bool Game::GameLoop() {
    const int32_t targetFrameLength = (int32_t)(1000 / fps);
    uint32_t previousTime, currentTime, deltaTime;
    currentTime = SDL_GetTicks();
    InputProcessor::GetInputFromDevice();

    try {
        while(1==1) {
            previousTime = currentTime;
            currentTime = SDL_GetTicks();
            deltaTime = currentTime - previousTime;

            if(!Step(deltaTime)) {
                break;
            }

            PauseForRestOfFrame(targetFrameLength, SDL_GetTicks() - currentTime);
        }
    } catch (const std::exception& ex) {
        std::cout << "Game::GameLoop() failed: " << ex.what() << std::endl;
        return false;
    }
    return true;
}

int Game::Run() {
    try {
        if (GameLoop() == false) {
            std::cout << "Game loop failed!" << std::endl;
            CloseSDL(win, ren, screen);
            return 1;
        } else {
            CloseSDL(win, ren, screen);
            std::cout << "Successfully closed SDL" << std::endl;
            return 0;
        }
    } catch(std::exception& ex) {
        std::cout << "Game::Run() failed: " << ex.what() << std::endl;
        return 1;
    }
}

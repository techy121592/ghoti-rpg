/**
 * Copyright (C) 2017  David Welch & Ankit Singhania
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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

    screen  = new LoadScreen<GameScreen>(ren);
    screen->Setup();
    if(!screen->CheckSetup()) {
        std::cout << "Failed to setup the LoadingScreen: " << SDL_GetError() << std::endl;
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
        return std::make_tuple<SDL_Window*, SDL_Renderer*>(nullptr, nullptr);
    }

    SDL_Window* win = SDL_CreateWindow("Ghoti RPG/Action Adventure", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return std::make_tuple<SDL_Window*, SDL_Renderer*>(nullptr, nullptr);
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return std::make_tuple<SDL_Window*, SDL_Renderer*>(nullptr, nullptr);
    }

    return std::make_tuple(win, ren);
}

void Game::CloseSDL(SDL_Window*& win, SDL_Renderer*& ren, Screen*& screen) {
    delete screen;

    if(ren != nullptr) {
        SDL_DestroyRenderer(ren);
    }

    if(win != nullptr) {
        SDL_DestroyWindow(win);
    }

    SDL_Quit();
}

void Game::PauseForRestOfFrame(const uint32_t targetFrameLength, const uint32_t deltaTime) {
    if(targetFrameLength > deltaTime) SDL_Delay((uint32_t)(targetFrameLength - deltaTime));
}

void Game::FireOffThreadsToUpdateAndGetInput(Screen* screenPointer, const uint32_t deltaTime, const InputData inputData) {
    ThreadPool::AddTask([screenPointer, deltaTime, inputData]() {
        screenPointer->Update(deltaTime, inputData);
    }, true);

    ThreadPool::AddTask([]() {
        InputProcessor::GetInputFromDevice();
    }, true);
}

void Game::Draw(std::list<DrawableComponent*> drawableComponentsData) {
    SDL_RenderClear(ren);

    for(DrawableComponent* drawableComponent : drawableComponentsData) {
        drawableComponent->Draw(ren);
    }

    SDL_RenderPresent(ren);
}

bool Game::Step(const uint32_t deltaTime) {
    if(screen == nullptr) {
        return false;
    }

    std::list<DrawableComponent*> drawableComponentsData = screen->CloneDrawables();

    FireOffThreadsToUpdateAndGetInput(screen, deltaTime, InputProcessor::GetInputData());
    Draw(drawableComponentsData);

    drawableComponentsData.clear();

    while(ThreadPool::LoopLocked()) {
        SDL_Delay(1);
    }

    if(screen != screen->NextScreen()) {
        Screen* tempScreen = screen->NextScreen();
        delete screen;
        screen = tempScreen;

        if(screen == nullptr) {
            return false;
        } else if(!screen->CheckSetup()) {
            screen = nullptr;
            return false;
        }
    }
    return true;
}

bool Game::GameLoop() {
    auto targetFrameLength = (uint32_t)(1000 / fps);
    uint32_t previousTime, currentTime, deltaTime;
    currentTime = SDL_GetTicks();
    InputProcessor::GetInputFromDevice();

    try {
        while(true) {
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
        if (!GameLoop()) {
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

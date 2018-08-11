/**
 * Copyright (C) 2018 David Welch
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

#include "utilities/thread_safe_renderer.h"
#include "game.h"

Screen* Game::screen = nullptr;

Game::Game(const uint32_t width, const uint32_t height, const uint32_t fps) {
    try {
        this->fps = fps;

        win = SetupSDL(width, height);
        std::cout << "Trying to get ThreadSafeRender to check renderer status" << std::endl;
        auto threadSafeRenderer = new ThreadSafeRenderer();
        std::cout << "Got ThreadSafeRender to check renderer status" << std::endl;
        if (this->win == nullptr || threadSafeRenderer->Renderer == nullptr) {
            CloseSDL(win, screen);
        }
        delete threadSafeRenderer;
        std::cout << "Done checking status" << std::endl;

        screen  = new LoadScreen<MainMenuScreen>();
    } catch(std::exception& exception) {
        CloseSDL(win, screen);
        //TODO: Log exception
    }
}

Game::~Game() {
    ThreadPool::TerminateThreads();
}

SDL_Window* Game::SetupSDL(const uint32_t width, const uint32_t height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return nullptr;
    }

    SDL_Window* win = SDL_CreateWindow("Ghoti RPG/Action Adventure", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        SDL_Quit();
        return nullptr;
    }

    ThreadSafeRenderer::SetUpRenderer(win);
    std::cout << "Trying to get ThreadSafeRender to set blend mode" << std::endl;
    auto threadSafeRenderer = new ThreadSafeRenderer();
    std::cout << "Got ThreadSafeRender to set blend mode" << std::endl;
    SDL_SetRenderDrawBlendMode(threadSafeRenderer->Renderer, SDL_BLENDMODE_BLEND);
    delete threadSafeRenderer;
    std::cout << "Done setting blend mode" << std::endl;

    return win;
}

void Game::CloseSDL(SDL_Window*& win, Screen*& screen) {
    delete screen;

    std::cout << "Trying to lock renderer to close SDL" << std::endl;
    auto threadSafeRenderer = new ThreadSafeRenderer();
    std::cout << "Got ThreadSafeRender to close SDL" << std::endl;
    if(threadSafeRenderer->Renderer != nullptr) {
        SDL_DestroyRenderer(threadSafeRenderer->Renderer);
    }
    delete threadSafeRenderer;
    std::cout << "Done closing SDL" << std::endl;

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
    std::cout << "Trying to lock renderer to render screen" << std::endl;
    auto threadSafeRenderer = new ThreadSafeRenderer();
    std::cout << "Got ThreadSafeRender to render screen" << std::endl;
    SDL_RenderClear(threadSafeRenderer->Renderer);

    for(DrawableComponent* drawableComponent : drawableComponentsData) {
        drawableComponent->Draw(threadSafeRenderer->Renderer);
    }

    SDL_RenderPresent(threadSafeRenderer->Renderer);
    delete threadSafeRenderer;
    std::cout << "Done rendering screen" << std::endl;
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
        if(tempScreen == nullptr) {
            return false;
        }

        delete screen;
        screen = tempScreen;

        if(screen == nullptr) {
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
            CloseSDL(win, screen);
            return 1;
        } else {
            CloseSDL(win, screen);
            return 0;
        }
    } catch(std::exception& ex) {
        std::cout << "Game::Run() failed: " << ex.what() << std::endl;
        return 1;
    }
}

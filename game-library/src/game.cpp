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

#include "game.h"

Screen* Game::screen = nullptr;

Game::Game(const uint32_t width, const uint32_t height, const uint32_t fps) {
    try {
        this->fps = fps;
        win = SetupSDL(width, height);
        if (this->win == nullptr) {
            CloseSDL(win, screen);
        }
        screen  = new LoadScreen<MainMenuScreen>();
        while(!screen->IsReady()) {
            SDL_Delay(10);
        }
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

    RenderQueue::StartQueueWatcher();
    auto renderQueue = new RenderQueue();
    renderQueue->AddSetUpRenderer(win, [](){});
    delete renderQueue;

    return win;
}

void Game::CloseSDL(SDL_Window*& win, Screen*& screen) {
    delete screen;
    RenderQueue::StopQueueWatcher();
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
    auto renderQueue = new RenderQueue();
    renderQueue->AddClear([](){});
    for(DrawableComponent* drawableComponent : drawableComponentsData) {
        drawableComponent->Draw(renderQueue);
    }
    renderQueue->AddPresent([](){});
    delete renderQueue;
}

bool Game::Step(const uint32_t deltaTime) {
    if(screen == nullptr) {
        return false;
    } else if(!screen->IsReady()) {
        return true;
    }

    std::list<DrawableComponent*> drawableComponentsData = screen->CloneDrawables();

    FireOffThreadsToUpdateAndGetInput(screen, deltaTime, InputProcessor::GetInputData());
    Draw(drawableComponentsData);

    drawableComponentsData.clear();

    while(ThreadPool::LoopLocked() || !RenderQueue::IsEmpty()) {
        SDL_Delay(5);
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
        std::cerr << "Game::GameLoop() failed: " << ex.what() << std::endl;
        return false;
    }
    return true;
}

int Game::Run() {
    try {
        if (!GameLoop()) {
            std::cerr << "Game loop failed!" << std::endl;
            CloseSDL(win, screen);
            return 1;
        } else {
            CloseSDL(win, screen);
            return 0;
        }
    } catch(std::exception& ex) {
        std::cerr << "Game::Run() failed: " << ex.what() << std::endl;
        return 1;
    }
}

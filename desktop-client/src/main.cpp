#include <iostream>
#include <string>
#include <SDL.h>

#include <test-class.h>

#include "res_path.h"

int setupSDL(SDL_Window*& win, SDL_Renderer*& ren) {
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

int loadImage(std::string fileName, SDL_Renderer* ren, SDL_Texture*& tex) {
    std::string imagePath = getResourcePath("images") + fileName;
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if (bmp == nullptr) {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

int runGame() {
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;

    if (setupSDL(win, ren)) {
        return 1;
    }

    if(win == nullptr) {
        std::cout << "Window is null" << std::endl;
        return 1;
    }

    if(ren == nullptr) {
        std::cout << "Renderer is null" << std::endl;
        return 1;
    }

    std::cout << "Resource path is: " << getResourcePath() << std::endl;
    SDL_Texture *tex = nullptr;
    if (loadImage("hello.bmp", ren, tex)) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    //A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
    for (int i = 0; i < 3; ++i) {
        //First clear the renderer
        SDL_RenderClear(ren);
        //Draw the texture
        SDL_RenderCopy(ren, tex, NULL, NULL);
        //Update the screen
        SDL_RenderPresent(ren);
        //Take a quick break after all that hard work
        SDL_Delay(1000);
    }

    // Just proving we can use the code from the other library here.
    TestClass testClass;
    std::cout << "TestClass.GetNumber(): " << testClass.GetNumber() << std::endl;

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    std::cout << "Game completed successfully" << std::endl;
    return 0;
}

int main(int, char**) {
    return runGame();
}

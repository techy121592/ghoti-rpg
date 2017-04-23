#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include "screen.h"
#include "hello_screen.h"
#include "resource_loader.h"
#include "thread_pool.h"

template<class T>
class LoadScreen : public Screen {
private:
    static Screen* nextScreenHolder;
    static bool doneLoading;
    SDL_Texture* loadingTexture;
    SDL_Renderer* ren;
public:
    LoadScreen<T>(SDL_Renderer* ren);
    ~LoadScreen();
    bool CheckSetup();
    void Update(const uint32_t deltaTime, const InputData inputData);
    void MainThreadActivity();
};

#endif

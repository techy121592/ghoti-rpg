#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include "screen.h"
#include "hello_screen.h"
#include "game_screen.h"
#include "utilities/resource_loader.h"
#include "utilities/thread_pool.h"

template<class T>
class LoadScreen : public Screen {
private:
    static Screen* nextScreenHolder;
    static bool doneLoading;
    SDL_Texture* loadingTexture;
public:
    explicit LoadScreen<T>(SDL_Renderer* ren);
    ~LoadScreen();
    bool CheckSetup();
    void Update(uint32_t deltaTime, InputData inputData);
};

#endif

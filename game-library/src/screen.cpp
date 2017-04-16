#include "screen.h"

void Screen::RenderScreen(SDL_Renderer* ren) {
    SDL_RenderClear(ren);
    RenderComponents(ren);
    SDL_RenderPresent(ren);
}

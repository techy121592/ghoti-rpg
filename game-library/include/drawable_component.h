#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include <SDL.h>

class DrawableComponent {
private:
    SDL_Texture* texture;
    int x, y, height, width, frame;
public:
    DrawableComponent(int x, int y, int width, int height, int frame, SDL_Texture* texture);
    void Draw(SDL_Renderer* ren);
    DrawableComponent* Clone();
};

#endif

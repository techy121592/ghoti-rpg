#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include <SDL.h>

class DrawableComponent {
private:
    SDL_Texture* texture;
    int x, y, height, width, frame;
public:
    DrawableComponent(const int32_t x, const int32_t y, const int32_t width, const int32_t height, const int32_t frame, SDL_Texture* texture);
    ~DrawableComponent();
    void Draw(SDL_Renderer* ren);
    DrawableComponent* Clone();
};

#endif

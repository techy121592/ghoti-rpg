#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include <SDL.h>

class DrawableComponent {
private:
    SDL_Texture* texture;
    SDL_Rect sourceRectangle, destinationRectangle;
public:
    DrawableComponent(const SDL_Rect destinationRectangle, const SDL_Rect sourceRectangle, SDL_Texture* texture);
    DrawableComponent(const int32_t x, const int32_t y, const int32_t width, const int32_t height, const int32_t frame, SDL_Texture* texture);
    ~DrawableComponent();
    void Draw(SDL_Renderer* ren);
    DrawableComponent* Clone();
};

#endif

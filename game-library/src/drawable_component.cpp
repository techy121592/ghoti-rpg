#include "drawable_component.h"

DrawableComponent::DrawableComponent(int x, int y, int height, int width, int frame, SDL_Texture* texture) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->frame = frame;
    this->texture = texture;
}

void DrawableComponent::Draw(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, texture, NULL, NULL);
}

DrawableComponent* DrawableComponent::Clone() {
    return new DrawableComponent(x, y, height, width, frame, texture);
}

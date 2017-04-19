#include "drawable_component.h"

DrawableComponent::DrawableComponent(const int32_t x, const int32_t y, const int32_t height, const int32_t width, const int32_t frame, SDL_Texture* texture) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->frame = frame;
    this->texture = texture;
}

DrawableComponent::~DrawableComponent() {
    SDL_DestroyTexture(texture);
}

void DrawableComponent::Draw(SDL_Renderer* ren) {
    SDL_RenderCopy(ren, texture, NULL, NULL);
}

DrawableComponent* DrawableComponent::Clone() {
    return new DrawableComponent(x, y, height, width, frame, texture);
}

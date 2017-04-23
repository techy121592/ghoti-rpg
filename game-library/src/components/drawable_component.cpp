#include "components/drawable_component.h"
#include <iostream>

DrawableComponent::DrawableComponent(const int32_t x, const int32_t y, const int32_t width, const int32_t height, const int32_t frame, SDL_Texture* texture) {
    this->texture = texture;

    int32_t textureWidth, textureHeight;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &textureWidth, &textureHeight);

    uint16_t framesWide = textureWidth / width;

    this->sourceRectangle = {(frame%framesWide) * width, (frame/framesWide) * height, width, height};
    this->destinationRectangle = {x, y, width, height};
}

DrawableComponent::DrawableComponent(const SDL_Rect destinationRectangle, const SDL_Rect sourceRectangle, SDL_Texture* texture) {
    this->destinationRectangle = destinationRectangle;
    this->sourceRectangle = sourceRectangle;
    this->texture = texture;
}

DrawableComponent::~DrawableComponent() {
    SDL_DestroyTexture(texture);
}

void DrawableComponent::Draw(SDL_Renderer* ren) {
    if(texture == nullptr) {
        std::cout << "no texture" << std::endl;
    } else {
        std::cout << "drawing" << std::endl;
    }
    SDL_RenderCopy(ren, texture, &sourceRectangle, &destinationRectangle);
}

DrawableComponent* DrawableComponent::Clone() {
    return new DrawableComponent(sourceRectangle, destinationRectangle, texture);
}

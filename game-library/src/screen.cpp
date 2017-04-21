#include "screen.h"

Screen* Screen::NextScreen() {
    return nextScreen;
}

std::list<DrawableComponent*> Screen::CloneDrawables() {
    std::list<DrawableComponent*> tempListOfDrawableComponents = {};
    for(DrawableComponent* drawableComponent : components) {
        tempListOfDrawableComponents.push_back(drawableComponent->Clone());
    }
    return tempListOfDrawableComponents;
}

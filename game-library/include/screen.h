#ifndef SCREEN_H
#define SCREEN_H

#include <list>
#include <SDL.h>
#include "input_data.h"
#include "drawable_component.h"

class Screen {
protected:
    std::list<DrawableComponent*> components = {}; // Should probably make some other type to hold on, but for now this is good enough
public:
    virtual ~Screen() {
        for(DrawableComponent* component : components) {
            delete component;
        }
    };
    virtual Screen* Update(const uint32_t deltaTime, InputData* inputData) = 0;
    virtual bool CheckSetup() = 0;

    std::list<DrawableComponent*> CloneDrawables();
};

#endif

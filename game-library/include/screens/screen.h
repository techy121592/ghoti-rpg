#ifndef SCREEN_H
#define SCREEN_H

#include <list>
#include <SDL.h>
#include "utilities/input_data.h"
#include "components/drawable_component.h"

class Screen {
protected:
    std::list<DrawableComponent*> components = {}; // Should probably make some other type to hold on, but for now this is good enough
    Screen* nextScreen = this;
public:
    virtual ~Screen() {
        for(DrawableComponent* component : components) {
            delete component;
        }
        components.clear();
    };
    virtual void Update(const uint32_t deltaTime, const InputData inputData) = 0;
    virtual bool CheckSetup() = 0;

    Screen* NextScreen();
    std::list<DrawableComponent*> CloneDrawables();
};

#endif

#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <SDL.h>
#include "input_processor.h"

class InputProcessor {
public:
    static InputData GetInput() {
        SDL_Event events;
        InputData inputData;

        while(SDL_PollEvent(&events)) {
            // This is where we get input
            if(events.type == SDL_QUIT) {
                inputData.Quit = true;
            }
        }

        return inputData;
    }
};

#endif

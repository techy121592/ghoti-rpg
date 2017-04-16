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
            switch(events.type) {
                // This is where we get input
                case SDL_QUIT:
                    inputData.Quit = true;
            }
        }

        return inputData;
    }
};

#endif

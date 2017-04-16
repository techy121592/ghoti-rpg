#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <SDL.h>
#include "input_processor.h"

class InputProcessor {
    static InputData ProcessKeyDown(SDL_Keycode keycode, InputData inputData) {
        switch(keycode) {
            case SDLK_ESCAPE:
                inputData.Quit = true;
        }
        return inputData;
    }
public:
    static InputData GetInput() {
        SDL_Event event;
        InputData inputData;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                // This is where we get input
                case SDL_QUIT:
                    inputData.Quit = true;
                    break;
                case SDL_KEYDOWN:
                    inputData = ProcessKeyDown(event.key.keysym.sym, inputData);
                    break;
            }
            if(inputData.Quit) {
                break;
            }
        }

        return inputData;
    }
};

#endif

#include "utilities/input_processor.h"

InputData InputProcessor::inputData;

InputData InputProcessor::ProcessKeyEvent(const SDL_Keycode keycode, InputData inputData, const bool keyDown) {
    switch(keycode) {
        case SDLK_ESCAPE:
            inputData.Quit = keyDown;
    }
    return inputData;
}

InputData InputProcessor::GetInputData() {
    return inputData;
}

void InputProcessor::GetInputFromDevice() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                inputData.Quit = true;
                break;
            case SDL_KEYDOWN:
                inputData = ProcessKeyEvent(event.key.keysym.sym, inputData, true);
                break;
            case SDL_KEYUP:
                inputData = ProcessKeyEvent(event.key.keysym.sym, inputData, false);
                break;
        }
        if(inputData.Quit) {
            break;
        }
    }
}

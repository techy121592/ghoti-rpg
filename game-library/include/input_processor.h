#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <iostream>
#include <SDL.h>
#include "input_processor.h"
#include "input_data.h"

class InputProcessor {
private:
    static InputData inputData;

    static InputData ProcessKeyEvent(const SDL_Keycode keycode, InputData inputData, const bool keyDown);
public:
    static InputData GetInputData();
    static void GetInputFromDevice();
};

#endif

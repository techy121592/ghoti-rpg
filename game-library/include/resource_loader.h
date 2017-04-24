#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class ResourceLoader {
private:
    static std::string GetResourcePath(const std::string &subDir = "");

public:
    static SDL_Texture* LoadImage(const std::string &fileName, SDL_Renderer* ren);
};

#endif

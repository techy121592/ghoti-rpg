#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class ResourceLoader {
private:
    static std::string GetResourcePath(const std::string &subDir = "") {
    #ifdef _WIN32
        const char PATH_SEP = '\\';
    #else
        const char PATH_SEP = '/';
    #endif
        static std::string baseRes;
        if (baseRes.empty()) {
            char *basePath = SDL_GetBasePath();
            if (basePath){
                baseRes = basePath;
                SDL_free(basePath);
            }
            else {
                std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
                return "";
            }

            size_t pos = baseRes.rfind("bin");
            baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
            std::cout << "Resource path is: " << baseRes << std::endl;
        }

        return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
    }

public:
    static SDL_Texture* LoadImage(const std::string &fileName, SDL_Renderer* ren) {
        static std::string imagePath;
        if(imagePath.empty()) {
            imagePath = ResourceLoader::GetResourcePath("images") + fileName;
        }

        SDL_Texture* tex = IMG_LoadTexture(ren, imagePath.c_str());
        if (tex == nullptr) {
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        return tex;
    }
};

#endif

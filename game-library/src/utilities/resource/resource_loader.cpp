/**
 * Copyright (C) 2018 David Welch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "utilities/resource/resource_loader.h"

std::string ResourceLoader::GetResourcePath(const std::string &subDir) {
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

        baseRes = baseRes + "res" + PATH_SEP;
    }

    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

SDL_Surface* ResourceLoader::LoadImage(const std::string &fileName) {
    try {
        SDL_Surface* image = IMG_Load((ResourceLoader::GetResourcePath("images") + fileName).c_str());
        
        if (image == nullptr) {
            std::cerr << "IMG_Load Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        return image;
    } catch (const std::exception& ex) {
        std::cerr << "ResourceLoader::LoadImage() failed: " << ex.what() << std::endl;
        return nullptr;
    }
}

TileMap* ResourceLoader::LoadMap(const std::string &fileName) {
    try {
        std::string filePath = ResourceLoader::GetResourcePath("maps") + fileName;
        tinyxml2::XMLDocument mapFile;
        mapFile.LoadFile(filePath.c_str());
        std::list<Tile*> tiles;

        auto rootElement = mapFile.FirstChildElement("map");
        auto playerZ = static_cast<uint32_t>(std::stoi(rootElement->FirstChildElement("properties")->FirstChildElement("property")->Attribute("value")));
        auto tileSetElement = rootElement->FirstChildElement("tileset");
        auto imageElement = tileSetElement->FirstChildElement("image");
        auto imageFileName = imageElement->Attribute("source");
        auto tileWidth = static_cast<uint32_t>(std::stoi(tileSetElement->Attribute("tilewidth")));
        auto tileHeight = static_cast<uint32_t>(std::stoi(tileSetElement->Attribute("tileheight")));

        auto tileSet = new TileSet(tileWidth, tileHeight, 1, imageFileName);
        while(!tileSet->IsReady()) {
            SDL_Delay(10);
        }

        uint32_t maxRows = 0;
        uint32_t maxCols = 0;

        for(auto layerElement = rootElement->FirstChildElement("layer"); layerElement != nullptr; layerElement = layerElement->NextSiblingElement("layer")) {
            auto layerZ = static_cast<uint32_t>(std::stoi(layerElement->FirstChildElement("properties")->FirstChildElement("property")->Attribute("value")));
            std::string layerWidthString = layerElement->Attribute("width");
            std::string layerHeightString = layerElement->Attribute("height");
            auto layerWidth = static_cast<uint32_t>(std::stoi(layerWidthString));
            auto layerHeight = static_cast<uint32_t>(std::stoi(layerHeightString));

            maxRows = maxRows >= layerHeight ? maxRows : layerHeight;
            maxCols = maxCols >= layerWidth ? maxCols : layerWidth;

            uint32_t col = 0;
            uint32_t row = 0;

            for(auto tileElement = layerElement->FirstChildElement("data")->FirstChildElement("tile"); tileElement != nullptr; tileElement = tileElement->NextSiblingElement("tile")) {
                if(col >= layerWidth) {
                    col = 0;
                    row++;
                }
                auto tileId = std::stoi(tileElement->Attribute("gid")) - 1;
                if(tileId > -1) {
                    tiles.emplace_back(tileSet->CreateTile(col, row, layerZ, static_cast<uint32_t>(tileId)));
                }
                col++;
            }
        }
        return new TileMap(maxRows, maxCols, tileWidth, tileHeight, playerZ, tiles);
    } catch (const std::exception& ex) {
        std::cerr << "ResourceLoader::LoadMap() failed: " << ex.what() << std::endl;
        return nullptr;
    }
}

void ResourceLoader::LoadControllerMap() {
    SDL_GameControllerAddMappingsFromFile((ResourceLoader::GetResourcePath("") + "gamecontrollerdb.txt").c_str());
}

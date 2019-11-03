/**
 * Copyright (C) 2018 David Welch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; only version 2
 * of the License.
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

#include <settings/button-type.h>
#include "utilities/resource/resource-loader.h"

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
        std::vector<Tile*> tiles;

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
    SDL_GameControllerAddMappingsFromFile((ResourceLoader::GetResourcePath("settings") + "gamecontrollerdb.txt").c_str());
}

MainMenuSettings ResourceLoader::LoadMainMenuSettings() {
    std::vector<ButtonSettings> buttonsSettingsVector;
    std::string filePath = ResourceLoader::GetResourcePath("settings") + "main-menu.xml";
    tinyxml2::XMLDocument mainMenuSettingsXMLDocument;
    mainMenuSettingsXMLDocument.LoadFile(filePath.c_str());;
    auto rootElement = mainMenuSettingsXMLDocument.FirstChildElement("main-menu");

    for(auto buttonElement = rootElement->FirstChildElement(); buttonElement != nullptr; buttonElement = buttonElement->NextSiblingElement()) {
        auto x = static_cast<uint32_t>(std::stoi(buttonElement->Attribute("x")));
        auto y = static_cast<uint32_t>(std::stoi(buttonElement->Attribute("y")));
        auto width = static_cast<uint32_t>(std::stoi(buttonElement->Attribute("width")));
        auto height = static_cast<uint32_t>(std::stoi(buttonElement->Attribute("height")));
        auto defaultFrame = static_cast<uint32_t>(std::stoi(buttonElement->Attribute("defaultFrame")));
        auto selectedFrame = static_cast<uint32_t>(std::stoi(buttonElement->Attribute("selectedFrame")));
        auto imagePath = buttonElement->Attribute("image");
        auto type = buttonElement->Name();
        bool defaultButton = strncmp(buttonElement->Attribute("default"), "true", 4) == 0;
        auto buttonType = ButtonType::None;
        std::string above = buttonElement->Attribute("above");
        std::string below = buttonElement->Attribute("below");
        std::string left = buttonElement->Attribute("left");
        std::string right = buttonElement->Attribute("right");
        std::string name = buttonElement->Attribute("name");

        if (strncmp(type, "load-map", 8) == 0) {
            buttonType = ButtonType::LoadMap;
        } else if (strncmp(type, "exit-game", 9) == 0) {
            buttonType = ButtonType::ExitGame;
        }

        buttonsSettingsVector.emplace_back(ButtonSettings(x, y, width, height, defaultFrame, selectedFrame, imagePath, buttonType, defaultButton, above, below, left, right, name));
    }

    return MainMenuSettings(buttonsSettingsVector);
}

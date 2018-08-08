/**
 * Copyright (C) 2017  David Welch & Ankit Singhania
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

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "components/drawable-components/tiles/tile.h"
#include "components/drawable-components/tiles/tile_map.h"
#include "components/drawable-components/tiles/tile_set.h"
#include "tinyxml2.h"

class ResourceLoader {
private:
    static std::string GetResourcePath(const std::string &subDir = "");

public:
    static SDL_Texture* LoadImage(const std::string &fileName, SDL_Renderer* ren);
    static TileMap* LoadMap(const std::string &fileName, SDL_Renderer* ren);
};

#endif
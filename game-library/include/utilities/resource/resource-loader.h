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

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tinyxml2.h"
#include "components/drawable-components/tiles/tile.h"
#include "components/drawable-components/tiles/tile-map.h"
#include "components/drawable-components/tiles/tile-set.h"
#include "components/drawable-components/button.h"
#include "screens/screen.h"
#include "settings/main-menu-settings.h"

class ResourceLoader {
private:
    static std::string GetResourcePath(const std::string &subDir = "");

public:
    static SDL_Surface* LoadImage(const std::string &fileName);
    static TileMap* LoadMap(const std::string &fileName);
    static void LoadControllerMap();
    static MainMenuSettings LoadMainMenuSettings();
};

#endif

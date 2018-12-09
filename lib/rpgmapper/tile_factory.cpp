/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/tile_factory.hpp>
#include "tiles/color_tile.hpp"

using namespace rpgmapper::model;


TilePointer TileFactory::create(TileType tileType, rpgmapper::model::Tile::Attributes & attributes) {
    
    switch (tileType) {
    
    case TileType ::color:
        return TilePointer{new rpgmapper::model::tiles::ColorTile{attributes}};
    }
    
    return TilePointer{nullptr};
}

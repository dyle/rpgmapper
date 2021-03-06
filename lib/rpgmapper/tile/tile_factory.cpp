/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/tile/tile_factory.hpp>

#include "color_tile.hpp"
#include "shape_tile.hpp"

using namespace rpgmapper::model::tile;


TilePointer TileFactory::create(TileType tileType, Tile::Attributes attributes) {
    
    switch (tileType) {
    
        case TileType::color:
            return TilePointer{new ColorTile{attributes}};
            
        case TileType::shape:
            return TilePointer{new ShapeTile{attributes}};
    }
    
    return TilePointer{nullptr};
}

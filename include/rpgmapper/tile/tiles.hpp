/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_TILES_HPP
#define RPGMAPPER_MODEL_TILE_TILES_HPP

#include <vector>

#include <rpgmapper/tile/tile_pointer.hpp>


namespace rpgmapper::model::tile {


/**
 * Tiles is a vector of tile pointers.
 */
using Tiles = std::vector<TilePointer>;


}


#endif

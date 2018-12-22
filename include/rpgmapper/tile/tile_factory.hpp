/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_FACTORY_HPP
#define RPGMAPPER_MODEL_TILE_FACTORY_HPP

#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/tile/tile_pointer.hpp>
#include <rpgmapper/tile/tile_types.hpp>


namespace rpgmapper {
namespace model {
namespace tile {


/**
 * The TileFactory creates tiles.
 */
class TileFactory {

public:
    
    /**
     * Constructor.
     */
    TileFactory() = delete;
    
    /**
     * Creates a specific tile with the given attributes.
     *
     * The attributes must somehow hint, which tile to create.
     *
     * @param   tileType        The type of tile to create.
     * @param   attributes      The initial set of attributes for the tile.
     * @return  A pointer to a tile (or nullptr if failed).
     */
    static TilePointer create(TileType tileType, Tile::Attributes attributes);
};


}
}
}


#endif

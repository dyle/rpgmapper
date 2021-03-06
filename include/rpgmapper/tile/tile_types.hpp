/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_TILE_TYPES_HPP
#define RPGMAPPER_MODEL_TILE_TILE_TYPES_HPP


namespace rpgmapper::model::tile {


/**
 * Different type of tiles we know.
 */
enum class TileType {
    color,            /**< A base color tile. */
    shape             /**< A tile holding a shape. */
};


}


#endif

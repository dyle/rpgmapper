/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_TILE_INSERT_MODES_HPP
#define RPGMAPPER_MODEL_TILE_TILE_INSERT_MODES_HPP

#include <QString>


namespace rpgmapper {
namespace model {
namespace tile {


/**
 * Different insertion modes of tiles when placed on a field on a map.
 */
enum class TileInsertMode {
    additive,            /**< The tile is inserted to the field along with other tiles (but itself). */
    exclusive            /**< A tile with this insertion  mode replaces all pre existing tiles on the same field. */
};


TileInsertMode getInsertModeFromString(QString mode);

}
}
}


#endif

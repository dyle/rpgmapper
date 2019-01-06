/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/tile/tile_insert_modes.hpp>

using namespace rpgmapper::model::tile;


rpgmapper::model::tile::TileInsertMode rpgmapper::model::tile::getInsertModeFromString(QString mode) {
    
    if (mode == "exclusive") {
        return TileInsertMode::exclusive;
    }
    
    return TileInsertMode::additive;
}

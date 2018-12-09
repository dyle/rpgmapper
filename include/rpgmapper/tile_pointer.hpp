/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_POINTER_HPP
#define RPGMAPPER_MODEL_TILE_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper {
namespace model {


// fwd
class Tile;


/**
 * A smart pointer to a single tile.
 */
using TilePointer = QSharedPointer<Tile>;


}
}


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_HPP
#define RPGMAPPER_MODEL_TILE_HPP

#include <map>

#include <QString>


namespace rpgmapper {
namespace model {


/**
 * A single tile on a field holds key-value pairs.
 *
 * A tile may be:
 *  - "river" - "south-west"
 *  - "wall" - "east"
 *  - "special" - "trapdoor"
 *
 * TODO: subject for redesign.
 */
using Tile = std::map<QString, QString>;


}
}


#endif

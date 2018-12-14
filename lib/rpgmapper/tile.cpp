/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/tile.hpp>

using namespace rpgmapper::model;


Tile::Tile(rpgmapper::model::Tile::Attributes & attributes) : attributes{attributes} {
}


QString Tile::getType() const {
    
    auto const & attributes = getAttributes();
    auto iter = attributes.find("type");
    if (iter == attributes.end()) {
        return QString::null;
    }
    return (*iter).second;
}

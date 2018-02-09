/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Impl::Impl(Region * region) : region{region}, backgroundLayer{new InvalidLayer} {
}


bool Map::Impl::applyJsonObject(QJsonObject const & json) {
    auto result = Nameable::applyJsonObject(json);
    return result;
}


LayerPointer const & Map::Impl::getBackgroundLayer() const {
    return backgroundLayer;
}


QJsonObject Map::Impl::getJsonObject() const {
    auto json = Nameable::getJsonObject();
    return json;
}

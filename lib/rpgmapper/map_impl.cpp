/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Impl::Impl(Region * region) : region{region} {
}


QJsonObject Map::Impl::getJsonObject() const {
    QJsonObject jsonObject;
    jsonObject["name"] = name;
    return jsonObject;
}
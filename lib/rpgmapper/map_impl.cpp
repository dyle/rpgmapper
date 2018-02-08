/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Impl::Impl(Region * region) : region{region} {
}


void Map::Impl::clear() {
    name.clear();
}


bool Map::Impl::applyJsonObject(QJsonObject const & json) {

    clear();

    if (!json.contains("name")) {
        return false;
    }
    if (!json["name"].isString()) {
        return false;
    }
    name = json["name"].toString();

    return true;
}


QJsonObject Map::Impl::getJsonObject() const {
    QJsonObject jsonObject;
    jsonObject["name"] = name;
    return jsonObject;
}
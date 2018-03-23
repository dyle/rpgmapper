/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "nameable.hpp"

using namespace rpgmapper::model;


bool Nameable::applyJsonObject(QJsonObject const & json) {
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

QJsonObject Nameable::getJsonObject(UNUSED rpgmapper::model::io::Content & content) const {

    QJsonObject jsonObject;
    jsonObject["name"] = name;
    return jsonObject;
}

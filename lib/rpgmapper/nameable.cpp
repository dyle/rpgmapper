/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


bool Nameable::applyJSON(QJsonObject const & json) {
    
    if (!json.contains("name") || !json["name"].isString()) {
        return false;
    }
    
    setName(json["name"].toString());
    return true;
}


void Nameable::clear() {
    name.clear();
    emit nameChanged();
}


QJsonObject Nameable::getJSON() const {
    QJsonObject json;
    json["name"] = name;
    return json;
}


void Nameable::setName(QString sname) {
    
    if (name == this->name) {
        return;
    }
    
    this->name = name;
    emit nameChanged();
}

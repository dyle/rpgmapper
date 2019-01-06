/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


Nameable::Nameable(QString name) : name{std::move(name)} {
}


bool Nameable::applyJSON(QJsonObject const & json) {
    
    if (!json.contains("name") || !json["name"].isString()) {
        return false;
    }
    
    setName(json["name"].toString());
    return true;
}


void Nameable::clear() {
    auto oldName = name;
    name.clear();
    emit nameChanged(oldName, name);
}


QJsonObject Nameable::getJSON() const {
    QJsonObject json;
    json["name"] = name;
    return json;
}


void Nameable::setName(QString name) {
    
    if (name == this->name) {
        return;
    }
    auto oldName = this->name;
    this->name = name;
    emit nameChanged(oldName, this->name);
}

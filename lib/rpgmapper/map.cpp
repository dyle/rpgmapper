#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>

#include "map_name_validator.hpp"

using namespace rpgmapper::model;


Map::Map(QString const & name, Region * region) : Nameable{name} {
    setParent(region);
    coordinateSystem = new CoordinateSystem;
}


Map::~Map() {
    delete coordinateSystem;
}


bool Map::applyJSON(QJsonObject const & json) {
    auto appliedName = Nameable::applyJSON(json);
    auto appliedLayerStack = LayerStack::applyJSON(json)
    auto appliedCoordinateSystem = coordinateSystem.applyJSON(json);
    return appliedName && appliedLayerStack && appliedCoordinateSystem;
}


QString Map::createNewMapName() {
    
    auto allMapNames = getAtlas()->getAllMapNames();
    int i = 1;
    QString candidate = QString("New Map %1").arg(QString::number(i));
    auto iter = allMapNames.find(candidate);
    while (iter != allMapNames.end()) {
        candidate = QString("New Map %1").arg(QString::number(++i));
        iter = allMapNames.find(candidate);
    }
    return candidate;
}


QJsonObject Map::getJSON() const {
    auto json = Nameable::getJSON();
    json["layers"] = LayerStack::getJSON();
    json["coordinate_system"] = coordinateSystem.getJSON();
    return json;
}


bool Map::isNameValid(QString name) {
    return MapNameValidator::isValid(std::move(name));
}


QSharedPointer<rpgmapper::model::Map> const & Map::null() {
    static QSharedPointer<rpgmapper::model::Map> nullMap{new InvalidMap};
    return nullMap;
}

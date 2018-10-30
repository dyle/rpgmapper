/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>


using namespace rpgmapper::model;


Map::Map(QString mapName, QString regionName) : Nameable{} {
    setName(mapName);
    setRegionName(regionName);
    coordinateSystem = new CoordinateSystem;
}


Map::~Map() {
    delete coordinateSystem;
}


bool Map::applyJSON(QJsonObject const & json) {
    auto appliedName = Nameable::applyJSON(json);
    auto appliedLayerStack = LayerStack::applyJSON(json);
    auto appliedCoordinateSystem = coordinateSystem->applyJSON(json);
    return appliedName && appliedLayerStack && appliedCoordinateSystem;
}


QString Map::createNewMapName() {
    
    auto allMapNames = Session::getCurrentSession()->getAllMapNames();
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
    json["coordinate_system"] = coordinateSystem->getJSON();
    return json;
}


bool Map::isNameValid(QString name) {
    return MapNameValidator::isValid(std::move(name));
}


QSharedPointer<rpgmapper::model::Map> const & Map::null() {
    static QSharedPointer<rpgmapper::model::Map> nullMap{new InvalidMap};
    return nullMap;
}


void Map::setName(QString const & name) {
    
    if (getName() != name) {
        if (Session::getCurrentSession()->findMap(name)->isValid()) {
            throw rpgmapper::model::exception::invalid_mapname();
        }
    }
    
    Nameable::setName(name);
}


void Map::setRegionName(QString regionName) {
    
    if (regionName == this->regionName) {
        return;
    }
    
    if (!Session::getCurrentSession()->findRegion(regionName)->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    this->regionName = regionName;
    emit changedRegion();
}

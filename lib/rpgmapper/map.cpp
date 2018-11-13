/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>


using namespace rpgmapper::model;


Map::Map(QString mapName, QString regionName, Session * session) 
        : Nameable{}, 
          SessionObject{session} {
    
    setName(std::move(mapName));
    setRegionName(std::move(regionName));
    coordinateSystem = QSharedPointer<CoordinateSystem>(new CoordinateSystem);
    layerStack.setMap(this);
}


bool Map::applyJSON(QJsonObject const & json) {
    auto appliedName = Nameable::applyJSON(json);
    auto appliedLayerStack = getLayers().applyJSON(json);
    auto appliedCoordinateSystem = coordinateSystem->applyJSON(json);
    return appliedName && appliedLayerStack && appliedCoordinateSystem;
}


QJsonObject Map::getJSON() const {
    auto json = Nameable::getJSON();
    json["layers"] = getLayers().getJSON();
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


void Map::setName(QString name) {
    
    if (getName() == name) {
        return;
    }
    if (!MapNameValidator::isValid(name)) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    auto session = getSession();
    if (!session) {
        throw exception::invalid_session();
    }

    if (session->findMap(name)->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    session->changeMapLookup(getName(), name);
    session->findRegion(getRegionName())->changeMapName(getName(), name);
    Nameable::setName(name);
}


void Map::setRegionName(QString regionName) {
    
    if (regionName == this->regionName) {
        return;
    }
    
    auto session = getSession();
    if (!session) {
        throw exception::invalid_session();
    }

    if (!session->findRegion(regionName)->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    this->regionName = regionName;
    emit changedRegion();
}


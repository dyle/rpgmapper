/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QJsonArray>

#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/region_name_validator.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


Region::Region(QString name, Session * session) : Nameable{}, SessionObject{session} {
    setName(std::move(name));
}


void Region::addMap(QString name) {
    
    if (maps.find(name) != maps.end()) {
        return;
    }
    
    auto session = getSession();
    if (!session) {
        throw exception::invalid_session();
    }

    auto map = session->findMap(name);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    maps.insert(name);
    map->setRegionName(getName());
    emit mapAdded(name);
}


bool Region::applyJSON(QJsonObject const & json) {
    
    maps.clear();
    if (json.contains("maps") && json["maps"].isArray()) {
        applyJSONMaps(json["maps"].toArray());
    }
    
    return true;
}


bool Region::applyJSONMaps(QJsonArray const & jsonArray) {
    
    bool applied = true;
    maps.clear();
    for (auto && json : jsonArray) {
        if (json.isString()) {
            maps.insert(json.toString());
        }
    }
    
    return applied;
}


void Region::changeMapName(QString oldName, QString newName) {
    if (maps.find(oldName) != maps.end()) {
        maps.erase(oldName);
        maps.insert(newName);
    }
}


bool Region::containsMap(QString map) const {
    return maps.find(map) != maps.end();
}


QJsonObject Region::getJSON() const {
    
    QJsonObject json = Nameable::getJSON();
    
    QJsonArray jsonMaps;
    for (auto const & mapName: getMapNames()) {
        jsonMaps.append(mapName);
    }
    json["maps"] = jsonMaps;
    
    return json;
}


QSharedPointer<rpgmapper::model::Region> const & Region::null() {
    static RegionPointer nullRegion{new InvalidRegion};
    return nullRegion;
}


void Region::removeMap(QString mapName) {
    
    auto map = maps.find(mapName);
    if (map != maps.end()) {
        return;
    }
    
    auto session = getSession();
    if (!session) {
        throw exception::invalid_session();
    }

    maps.erase(map);
    session->findMap(mapName)->setRegionName(QString::null);
    emit mapRemoved(mapName);
}


void Region::setName(QString name) {
    
    if (name == getName()) {
        return;
    }
    if (!RegionNameValidator::isValid(name)) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    auto session = getSession();
    if (!session) {
        throw exception::invalid_session();
    }

    auto region = session->findRegion(name);
    if (region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    session->changeRegionLookup(getName(), name);
    Nameable::setName(name);
    for (auto const & mapName : getMapNames()) {
        session->findMap(mapName)->setRegionName(name);
    }
}


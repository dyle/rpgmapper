/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QJsonArray>

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/region_name_validator.hpp>

using namespace rpgmapper::model;


Region::Region(QString name) : Nameable{std::move(name)} {
}


void Region::addMap(MapPointer map) {
    
    if (!map->isValid()) {
        throw exception::invalid_map{};
    }
    
    if (maps.find(map->getName()) != maps.end()) {
        return;
    }
    
    this->maps[map->getName()] = map;
    // TODO: add map connector: delete, name change
    emit mapAdded(map->getName());
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
            // TODO: maps.insert(json.toString());
        }
    }
    
    return applied;
}


MapPointer Region::getMap(QString name) {
    auto iter = maps.find(name);
    if (iter == maps.end()) {
        throw exception::invalid_mapname{};
    }
    return (*iter).second;
}


MapPointer const Region::getMap(QString name) const {
    auto iter = maps.find(name);
    if (iter == maps.end()) {
        throw exception::invalid_mapname{};
    }
    return (*iter).second;
}


QJsonObject Region::getJSON() const {
    
    QJsonObject json = Nameable::getJSON();
    
    QJsonArray jsonMaps;
    for (auto const & iter : getMaps()) {
        jsonMaps.append(iter.second->getName());
    }
    json["maps"] = jsonMaps;
    
    return json;
}


RegionPointer const & Region::null() {
    static RegionPointer nullRegion{new InvalidRegion};
    return nullRegion;
}


void Region::removeMap(QString mapName) {
    
    auto iter = maps.find(mapName);
    if (iter == maps.end()) {
        throw exception::invalid_mapname{};
    }
    
    maps.erase(iter);
    emit mapRemoved(mapName);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
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
    
    auto mapName = map->getName();
    this->maps[mapName] = map;
    connect(map.data(), &Nameable::nameChanged, this, &Region::mapNameChanged);
    emit mapAdded(mapName);
}


bool Region::applyJSON(QJsonObject const & json) {
    
    maps.clear();
    if (json.contains("maps") && json["maps"].isArray()) {
        applyJSONMaps(json["maps"].toArray());
    }
    
    return true;
}


bool Region::applyJSONMaps(QJsonArray const & jsonMaps) {
    
    for (auto && jsonMap : jsonMaps) {
        if (jsonMap.toObject().contains("name") && jsonMap.toObject()["name"].isString()) {
            auto map = MapPointer{new Map{jsonMap.toObject()["name"].toString()}};
            if (!map->applyJSON(jsonMap.toObject())) {
                return false;
            }
            addMap(map);
        }
    }

    return true;
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
    for (auto const & iter : maps) {
        jsonMaps.append(iter.second->getJSON());
    }
    json["maps"] = jsonMaps;
    
    return json;
}


std::set<QString> Region::getMapNames() const {
    
    std::set<QString> names;
    for (auto const & pair : maps) {
        names.insert(pair.second->getName());
    }
    return names;
}


void Region::mapNameChanged(QString oldName, QString newName) {
    
    auto iterOld = maps.find(oldName);
    if (iterOld == maps.end()) {
        return;
    }
    auto iterNew = maps.find(newName);
    if (iterNew != maps.end()) {
        throw exception::invalid_mapname{};
    }
    
    auto map = (*iterOld).second;
    maps.erase(iterOld);
    maps.emplace(newName, map);
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
    
    auto map = (*iter).second;
    maps.erase(iter);
    
    emit mapRemoved(mapName);
}

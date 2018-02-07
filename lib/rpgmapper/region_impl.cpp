/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QJsonArray>

#include <rpgmapper/atlas.hpp>
#include "region_impl.hpp"

using namespace rpgmapper::model;


Region::Impl::Impl(Atlas * atlas, Region * region) : atlas{atlas}, region{region} {
    if (region == nullptr) {
        throw std::invalid_argument("rpgmapper::model::Region::Impl::Impl() - region must not be nullptr.");
    }
}


QJsonObject Region::Impl::getJsonObject() const {

    QJsonObject jsonObject;
    jsonObject["name"] = name;

    QJsonArray jsonMaps;
    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&] (auto const & pair) { jsonMaps.append(pair.second->getJsonObject()); });
    jsonObject["maps"] = jsonMaps;

    return jsonObject;
}


std::set<QString> Region::Impl::getMapNames() const {

    std::set<QString> mapNames;
    std::for_each(std::begin(getMaps()),
                  std::end(getMaps()),
                  [&] (auto const & pair) { mapNames.insert(pair.second->getName()); });
    return mapNames;
}


MapPointer Region::Impl::createMap(QString const & name) {
    auto allMaps = getAtlas() ? getAtlas()->getAllMapNames() : getMapNames();
    if (allMaps.find(name) != allMaps.end()) {
        return MapPointer{new InvalidMap};
    }
    return maps.emplace(std::make_pair(name, MapPointer{new Map{name, region}, &Map::deleteLater})).first->second;
}


bool Region::Impl::removeMap(QString const & name) {
    auto iter = maps.find(name);
    if (iter == maps.end()) {
        return false;
    }
    maps.erase(iter);
    return true;
}

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


bool Region::Impl::addMap(MapPointer & map) {

    if (!map->isValid()) {
        return false;
    }
    auto regionFrom = map->getRegion();
    if (regionFrom != region) {
        regionFrom->removeMap(map->getName());
    }
    maps[map->getName()] = map;
    return true;
}


bool Region::Impl::applyJsonMapsArray(QJsonArray const & jsonMaps) {
    for (auto && jsonMap : jsonMaps) {
        if (jsonMap.toObject().contains("name") && jsonMap.toObject()["name"].isString()) {
            auto map = createMap(jsonMap.toObject()["name"].toString());
            if (!map->applyJsonObject(jsonMap.toObject())) {
                return false;
            }
        }
    }
    return true;
}


bool Region::Impl::applyJsonObject(QJsonObject const & json) {

    if (!Nameable::applyJsonObject(json)) {
        return false;
    }

    if (json.contains("maps")) {
        if (!json["maps"].isArray()) {
            return false;
        }
        if (!applyJsonMapsArray(json["maps"].toArray())) {
            return false;
        }
    }

    return true;
}


void Region::Impl::clear() {
    Nameable::clear();
    maps.clear();
}


MapPointer & Region::Impl::createMap(QString const & name) {

    static MapPointer invalidMap{new InvalidMap};
    auto allMaps = getAtlas() ? getAtlas()->getAllMapNames() : getMapNames();
    if (allMaps.find(name) != allMaps.end()) {
        return invalidMap;
    }
    return maps.emplace(std::make_pair(name, MapPointer{new Map{name, region}, &Map::deleteLater})).first->second;
}


MapPointer & Region::Impl::findMap(QString const & name) {

    static MapPointer invalidMap{new InvalidMap};
    auto iter = maps.find(name);
    if (iter != maps.end()) {
        return (*iter).second;
    }
    return invalidMap;
}


QString Region::Impl::getInvalidCharactersInName() {
    return R"raw(:\\*\?/)raw";
}


QJsonObject Region::Impl::getJsonObject(rpgmapper::model::io::Content & content) const {

    auto json = Nameable::getJsonObject(content);

    QJsonArray jsonMaps;
    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&] (auto const & pair) { jsonMaps.append(pair.second->getJsonObject(content)); });
    json["maps"] = jsonMaps;

    return json;
}


std::set<QString> Region::Impl::getMapNames() const {

    std::set<QString> mapNames;
    std::for_each(std::begin(getMaps()),
                  std::end(getMaps()),
                  [&] (auto const & pair) { mapNames.insert(pair.second->getName()); });
    return mapNames;
}


bool Region::Impl::isNameValid(QString name) {
    QRegExp regExp{QString{"[%1]"}.arg(getInvalidCharactersInName())};
    return (!name.isEmpty()) && (regExp.indexIn(name) == -1);
}


bool Region::Impl::removeMap(QString const & name) {
    auto iter = maps.find(name);
    if (iter == maps.end()) {
        return false;
    }
    maps.erase(iter);
    return true;
}

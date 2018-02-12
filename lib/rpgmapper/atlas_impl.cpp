/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QJsonArray>
#include "atlas_impl.hpp"

using namespace rpgmapper::model;


Atlas::Impl::Impl(Atlas * atlas) : atlas(atlas) {
    if (atlas == nullptr) {
        throw std::invalid_argument("rpgmapper::model::Atlas::Impl::Impl() - atlas must not be nullptr.");
    }
    setName(QObject::tr("New Atlas"));
    prozessor = ProzessorPointer{new Prozessor};
}

bool Atlas::Impl::applyJsonObject(QJsonObject const & json) {
    if (!Nameable::applyJsonObject(json)) {
        return false;
    }
    if (json.contains("regions")) {
        if (!json["regions"].isArray()) {
            return false;
        }
        if (!applyJsonRegionsArray(json["regions"].toArray())) {
            return false;
        }
    }
    return true;
}


bool Atlas::Impl::applyJsonRegionsArray(QJsonArray const & jsonRegions) {
    for (auto && jsonRegion : jsonRegions) {
        if (jsonRegion.toObject().contains("name") && jsonRegion.toObject()["name"].isString()) {
            auto region = createRegion(jsonRegion.toObject()["name"].toString());
            if (!region->applyJsonObject(jsonRegion.toObject())) {
                return false;
            }
        }
    }
    return true;
}


void Atlas::Impl::clear() {
    Nameable::clear();
    regions.clear();
}


RegionPointer Atlas::Impl::createRegion(QString const & name) {
    if (regions.find(name) != regions.end()) {
        return RegionPointer{new InvalidRegion};
    }
    auto pair = regions.emplace(std::make_pair(name,
                                               RegionPointer{new Region{name, this->atlas},
                                                             &Region::deleteLater}));
    changed = true;
    return pair.first->second;
}


MapPointer Atlas::Impl::findMap(QString const & name) {

    MapPointer map = MapPointer{new InvalidMap};

    for (auto & pair : regions) {
        map = pair.second->findMap(name);
        if (map->isValid()) {
            break;
        }
    }

    return map;
}


MapPointer const Atlas::Impl::findMap(QString const & name) const {

    MapPointer map = MapPointer{new InvalidMap};

    for (auto & pair : regions) {
        map = pair.second->findMap(name);
        if (map->isValid()) {
            break;
        }
    }

    return map;
}


RegionPointer Atlas::Impl::findRegion(QString const &name) {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return RegionPointer{new InvalidRegion};
    }
    return (*iter).second;
}


RegionPointer const Atlas::Impl::findRegion(QString const &name) const {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return RegionPointer{new InvalidRegion};
    }
    return (*iter).second;
}


std::set<QString> Atlas::Impl::getAllMapNames() const {

    std::set<QString> allMapNames;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) {
                      auto regionMapNames = pair.second->getMapNames();
                      allMapNames.insert(std::begin(regionMapNames), std::end(regionMapNames));
                  });
    return allMapNames;
}


std::set<QString> Atlas::Impl::getAllRegionNames() const {
    std::set<QString> regionNames;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) { regionNames.insert(pair.second->getName()); });
    return regionNames;
}


ProzessorPointer & Atlas::Impl::getCommandProzessor() {
    return prozessor;
}


ProzessorPointer const & Atlas::Impl::getCommandProzessor() const {
    return prozessor;
}


QJsonObject Atlas::Impl::getJsonObject() const {

    auto json = Nameable::getJsonObject();
    QJsonArray jsonRegions;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) { jsonRegions.append(pair.second->getJsonObject()); });
    json["regions"] = jsonRegions;

    return json;
}

void Atlas::Impl::init() {
    auto region = createRegion(QObject::tr("New Region 1"));
    region->createMap(QObject::tr("New Map 1"));
    changed = false;
}


bool Atlas::Impl::moveMap(MapPointer map, RegionPointer regionTo) {

    if (!map->isValid()) {
        return false;
    }
    if (!regionTo->isValid()) {
        return false;
    }

    return regionTo->addMap(map);
}


bool Atlas::Impl::removeRegion(QString const & name) {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return false;
    }
    regions.erase(iter);
    changed = true;
    return true;
}


void Atlas::Impl::resetChanged() {
    changed = false;
}


void Atlas::Impl::setName(QString const & name) {
    if (getName() == name) {
        return;
    }
    Nameable::setName(name);
    changed = true;
}

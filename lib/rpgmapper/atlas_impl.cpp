/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QJsonArray>
#include "atlas_impl.hpp"

using namespace rpgmapper::model;


Atlas::Impl::Impl(Atlas * atlas) : atlas(atlas), name{QObject::tr("New Atlas")} {
    if (atlas == nullptr) {
        throw std::invalid_argument("rpgmapper::model::Atlas::Impl::Impl() - atlas must not be nullptr.");
    }
}


RegionPointer Atlas::Impl::createRegion(QString const & name) {
    if (regions.find(name) != regions.end()) {
        return RegionPointer{new InvalidRegion};
    }
    auto pair = regions.emplace(std::make_pair(name, RegionPointer{new Region{name, this->atlas}, &Region::deleteLater}));
    changed = true;
    return pair.first->second;
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

QJsonObject Atlas::Impl::getJsonObject() const {

    QJsonObject jsonObject;
    jsonObject["name"] = getName();

    QJsonArray jsonRegions;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) { jsonRegions.append(pair.second->getJsonObject()); });
    jsonObject["regions"] = jsonRegions;

    return jsonObject;
}

RegionPointer const & Atlas::Impl::getRegion(QString const & name) const {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return std::move(RegionPointer{new InvalidRegion});
    }
    return (*iter).second;
}

void Atlas::Impl::init() {
    auto region = createRegion(QObject::tr("New Region 1"));
    region->createMap(QObject::tr("New Map 1"));
    changed = false;
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


void Atlas::Impl::setName(QString const & name) {
    if (this->name == name) {
        return;
    }
    this->name = name;
    changed = true;
}

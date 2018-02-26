/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/atlas.hpp>
#include <utility>
#include "region_impl.hpp"

using namespace rpgmapper::model;


Region::Region(QString const & name, Atlas * atlas) : QObject{atlas} {
    impl = std::make_shared<Region::Impl>(atlas, this);
    impl->setName(name);
}

bool Region::addMap(MapPointer & map) {

    if (!map->isValid()) {
        return false;
    }
    if (findMap(map->getName())->isValid()) {
        return false;
    }

    auto added = impl->addMap(map);
    connectMapSignals(map);
    emit mapAdded(getName(), map->getName());
    return added;
}


bool Region::applyJsonObject(QJsonObject const & json) {
    return impl->applyJsonObject(json);
}


void Region::changedMapName(QString nameBefore, QString nameAfter) {
    auto map = findMap(nameBefore);
    if (!map->isValid()) {
        return;
    }
    impl->removeMap(nameBefore);
    impl->addMap(map);
    emit mapNameChanged(getName(), nameBefore, std::move(nameAfter));
}


void Region::changedNumeralForAxis(QString mapName) {
    emit mapNumeralForAxisChanged(getName(), mapName);
}


void Region::connectMapSignals(MapPointer & map) {
    if (!map->isValid()) {
        return;
    }
    connect(map.data(), &Map::nameChanged, this, &Region::changedMapName);
    connect(map.data(), &Map::numeralForAxisChanged, this, &Region::changedNumeralForAxis);
    connect(map.data(), &Map::resized, this, &Region::resizedMap);
}


void Region::disconnectMapSignals(MapPointer & map) {
    if (!map->isValid()) {
        return;
    }
    disconnect(map.data());
}


Atlas * Region::getAtlas() {
    return impl->getAtlas();
}


MapPointer & Region::createMap(QString const & mapName) {
    auto & map = impl->createMap(mapName);
    if (map->isValid()) {
        connectMapSignals(map);
        emit mapCreated(getName(), mapName);
    }
    return map;
}


MapPointer Region::findMap(QString const & mapName) {
    return impl->findMap(mapName);
}


QJsonObject Region::getJsonObject() const {
    return impl->getJsonObject();
}

Maps const & Region::getMaps() const {
    return impl->getMaps();
}


std::set<QString> Region::getMapNames() const {
    return impl->getMapNames();
}


QString const & Region::getName() const {
    return impl->getName();
}


Region const & Region::nullRegion() {
    static InvalidRegion nullRegion;
    return nullRegion;
}


void Region::resizedMap(QString mapName) {
    emit mapResized(getName(), mapName);
}


void Region::removeMap(QString const & mapName) {
    auto map = findMap(mapName);
    if (!map->isValid()) {
        return;
    }
    impl->removeMap(mapName);
    disconnectMapSignals(map);
    emit mapRemoved(getName(), mapName);
}


void Region::setName(QString const & name) {
    auto nameBefore = impl->getName();
    if (name == nameBefore) {
        return;
    }
    impl->setName(name);
    emit nameChanged(nameBefore, name);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/atlas.hpp>
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
    emit mapAdded(map->getName());
    return added;
}


bool Region::applyJsonObject(QJsonObject const & json) {
    return impl->applyJsonObject(json);
}


Atlas * Region::getAtlas() {
    return impl->getAtlas();
}


MapPointer Region::createMap(QString const & name) {
    auto map = impl->createMap(name);
    if (map->isValid()) {
        emit mapCreated(name);
    }
    return map;
}


MapPointer Region::findMap(QString const & name) {
    return impl->findMap(name);
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


void Region::removeMap(QString const & name) {
    if (impl->removeMap(name)) {
        emit mapRemoved(name);
    }
}


void Region::setName(QString const & name) {
    if (name == impl->getName()) {
        return;
    }
    impl->setName(name);
    emit nameChanged();
}

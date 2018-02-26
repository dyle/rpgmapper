/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/atlas.hpp>
#include <utility>
#include "atlas_impl.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


Atlas::Atlas(QObject * parent) : QObject{parent} {
    impl = std::make_shared<Atlas::Impl>(this);
}


bool Atlas::applyJsonObject(QJsonObject json) {
    return impl->applyJsonObject(json);
}


void Atlas::connectRegionSignals(RegionPointer & region) {
    if (!region->isValid()) {
        return;
    }
    connect(region.data(), &Region::mapAdded, this, &Atlas::mapAdded);
    connect(region.data(), &Region::mapCreated, this, &Atlas::mapCreated);
    connect(region.data(), &Region::mapNameChanged, this, &Atlas::mapNameChanged);
    connect(region.data(), &Region::mapNumeralForAxisChanged, this, &Atlas::mapNumeralForAxisChanged);
    connect(region.data(), &Region::mapRemoved, this, &Atlas::mapRemoved);
    connect(region.data(), &Region::mapResized, this, &Atlas::mapResized);
    connect(region.data(), &Region::nameChanged, this, &Atlas::regionNameChanged);
}


RegionPointer & Atlas::createRegion(QString const & name) {
    auto & region = impl->createRegion(name);
    if (region->isValid()) {
        connectRegionSignals(region);
        emit regionCreated(name);
    }
    return region;
}


ProzessorPointer & Atlas::getCommandProzessor() {
    return impl->getCommandProzessor();
}


ProzessorPointer const & Atlas::getCommandProzessor() const {
    return impl->getCommandProzessor();
}


MapPointer & Atlas::findMap(QString const & name) {
    return impl->findMap(name);
}


MapPointer const & Atlas::findMap(QString const & name) const {
    return impl->findMap(name);
}


RegionPointer & Atlas::findRegion(QString const & name) {
    return impl->findRegion(name);
}


RegionPointer const & Atlas::findRegion(QString const & name) const {
    return impl->findRegion(name);
}


std::set<QString> Atlas::getAllMapNames() const {
    return impl->getAllMapNames();
}


std::set<QString> Atlas::getAllRegionNames() const {
    return impl->getAllRegionNames();
}


QJsonObject Atlas::getJsonObject() const  {
    return impl->getJsonObject();
}


QString const & Atlas::getFileName() const {
    return impl->getFileName();
}


QString const & Atlas::getName() const {
    return impl->getName();
}


Regions const & Atlas::getRegions() const {
    return impl->getRegions();
}


void Atlas::init() {
    impl->clear();
    setName(QObject::tr("New Atlas"));
    auto region = createRegion(QObject::tr("New Region 1"));
    region->createMap(QObject::tr("New Map 1"));
}


bool Atlas::isModified() const {
    return impl->isModified();
}


bool Atlas::moveMap(MapPointer map, RegionPointer regionTo) {
    auto regionFrom = findRegion(map->getRegionName());
    return impl->moveMap(map, std::move(regionTo));
}


Atlas const & Atlas::nullAtlas() {
    static InvalidAtlas nullAtlas;
    return nullAtlas;
}


void Atlas::removeRegion(QString const & name) {
    if (impl->removeRegion(name)) {
        emit regionRemoved(name);
    }
}


void Atlas::resetChanged() {
    impl->resetChanged();
}


void Atlas::setFileName(QString const & fileName) {
    impl->setFileName(fileName);
}


void Atlas::setName(QString const & name) {
    if (name == impl->getName()) {
        return;
    }
    impl->setName(name);
    emit nameChanged(name);
}

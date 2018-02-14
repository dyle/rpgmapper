/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/atlas.hpp>
#include "atlas_impl.hpp"

using namespace rpgmapper::model;


Atlas::Atlas(QObject * parent) : QObject{parent} {
    impl = std::make_shared<Atlas::Impl>(this);
    impl->init();
}


bool Atlas::applyJsonObject(QJsonObject json) {
    return impl->applyJsonObject(json);
}


RegionPointer Atlas::createRegion(QString const & name) {

    bool hasAlreadyChanged = impl->isModified();
    auto region = impl->createRegion(name);
    if (region->isValid()) {
        emit regionCreated(name);
        if (!hasAlreadyChanged) {
            emit changed();
        }
    }
    return region;
}


ProzessorPointer & Atlas::getCommandProzessor() {
    return impl->getCommandProzessor();
}


ProzessorPointer const & Atlas::getCommandProzessor() const {
    return impl->getCommandProzessor();
}


MapPointer Atlas::findMap(QString const & name) {
    return impl->findMap(name);
}


MapPointer const Atlas::findMap(QString const & name) const {
    return impl->findMap(name);
}


RegionPointer Atlas::findRegion(QString const & name) {
    return impl->findRegion(name);
}


RegionPointer const Atlas::findRegion(QString const & name) const {
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


QString const & Atlas::getName() const {
    return impl->getName();
}


Regions const & Atlas::getRegions() const {
    return impl->getRegions();
}


bool Atlas::isModified() const {
    return impl->isModified();
}


bool Atlas::moveMap(MapPointer map, RegionPointer regionTo) {

    bool hasAlreadyChanged = impl->isModified();
    auto regionFrom = findRegion(map->getRegionName());
    if (impl->moveMap(map, regionTo)) {
        if (!hasAlreadyChanged) {
            emit changed();
        }
        return true;
    }
    return false;
}


void Atlas::removeRegion(QString const & name) {

    bool hasAlreadyChanged = impl->isModified();
    if (impl->removeRegion(name)) {
        emit regionRemoved(name);
        if (!hasAlreadyChanged) {
            emit changed();
        }
    }
}


void Atlas::resetChanged() {
    impl->resetChanged();
}


void Atlas::setName(QString const & name) {

    bool hasAlreadyChanged = impl->isModified();
    impl->setName(name);
    if (impl->isModified() && !hasAlreadyChanged) {
        emit changed();
    }
}

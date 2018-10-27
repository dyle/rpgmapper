/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/atlas.hpp>
#include "atlas_impl.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


Atlas::Atlas(QObject * parent) : QObject{parent} {
    impl = std::make_shared<Atlas::Impl>(this);
    connect(getCommandProzessor().data(), &Processor::commandExecuted, this, &Atlas::commandExecuted);
}


bool Atlas::applyJSON(QJsonObject json) {
    return impl->applyJSON(json);
}


void Atlas::changedRegionName(QString nameBefore, QString nameAfter) {
    impl->renameRegion(nameBefore, nameAfter);
}


void Atlas::collectContent(rpgmapper::model::io::Content & content) const  {
    impl->collectIOContent(content);
}


void Atlas::connectRegionSignals(QSharedPointer<rpgmapper::model::Region> & region) {
    if (!region->isValid()) {
        return;
    }
    connect(region.data(), &Region::mapAdded, this, &Atlas::mapAdded);
    connect(region.data(), &Region::mapCreated, this, &Atlas::mapCreated);
    connect(region.data(), &Region::mapNameChanged, this, &Atlas::mapNameChanged);
    connect(region.data(), &Region::mapNumeralForAxisChanged, this, &Atlas::mapNumeralForAxisChanged);
    connect(region.data(), &Region::mapRemoved, this, &Atlas::mapRemoved);
    connect(region.data(), &Region::mapResized, this, &Atlas::mapResized);
    connect(region.data(), &Region::nameChanged, this, &Atlas::changedRegionName);
    connect(region.data(), &Region::nameChanged, this, &Atlas::regionNameChanged);
}


QSharedPointer<rpgmapper::model::Region> & Atlas::createRegion(QString const & name) {
    auto & region = impl->createRegion(name);
    if (region->isValid()) {
        connectRegionSignals(region);
        emit regionCreated(name);
    }
    return region;
}


QSharedPointer<rpgmapper::model::command::Processor> & Atlas::getCommandProzessor() {
    return impl->getCommandProzessor();
}


QSharedPointer<rpgmapper::model::command::Processor> const & Atlas::getCommandProzessor() const {
    return impl->getCommandProzessor();
}


ResourceDBPointer & Atlas::getResourceDB() {
    return impl->getResourceDB();
}


ResourceDBPointer const & Atlas::getResourceDB() const {
    return impl->getResourceDB();
}


QSharedPointer<rpgmapper::model::Map> & Atlas::findMap(QString const & name) {
    return impl->findMap(name);
}


QSharedPointer<rpgmapper::model::Map> const & Atlas::findMap(QString const & name) const {
    return impl->findMap(name);
}


QSharedPointer<rpgmapper::model::Region> & Atlas::findRegion(QString const & name) {
    return impl->findRegion(name);
}


QSharedPointer<rpgmapper::model::Region> const & Atlas::findRegion(QString const & name) const {
    return impl->findRegion(name);
}


std::set<QString> Atlas::getAllMapNames() const {
    return impl->getAllMapNames();
}


std::set<QString> Atlas::getAllRegionNames() const {
    return impl->getAllRegionNames();
}


QString Atlas::getInvalidCharactersInName() {
    return Atlas::Impl::getInvalidCharactersInName();
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


bool Atlas::isNameValid(QString name) {
    return Atlas::Impl::isNameValid(name);
}


bool Atlas::moveMap(QSharedPointer<rpgmapper::model::Map> map, QSharedPointer<rpgmapper::model::Region> regionTo) {
    auto regionFrom = findRegion(map->getRegionName());
    return impl->moveMap(map, std::move(regionTo));
}


QSharedPointer<rpgmapper::model::Atlas> const & Atlas::null() {
    static QSharedPointer<rpgmapper::model::Atlas> nullAtlas{new InvalidAtlas};
    return nullAtlas;
}


void Atlas::readIOContent(rpgmapper::model::io::Content const & content) {
    impl->readIOContent(content);
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

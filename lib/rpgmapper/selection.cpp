/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/selection.hpp>

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

using namespace rpgmapper::model;


Selection::Selection(QObject * parent) : QObject(parent) {
    atlas = QSharedPointer<rpgmapper::model::Atlas>{new InvalidAtlas{}};
    map = QSharedPointer<rpgmapper::model::Map>{new InvalidMap{}};
    region = QSharedPointer<rpgmapper::model::Region>{new InvalidRegion{}};
}


QString Selection::createNewMapName() const {

    auto allMapNames = getAtlas()->getAllMapNames();
    int i = 1;
    QString candidate = QString("New Map %1").arg(QString::number(i));
    auto iter = allMapNames.find(candidate);
    while (iter != allMapNames.end()) {
        candidate = QString("New Map %1").arg(QString::number(++i));
        iter = allMapNames.find(candidate);
    }
    return candidate;
}


QString Selection::createNewRegionName() const {

    auto allRegionNames = getAtlas()->getAllRegionNames();
    int i = 1;
    QString candidate = QString("New Region %1").arg(QString::number(i));
    auto iter = allRegionNames.find(candidate);
    while (iter != allRegionNames.end()) {
        candidate = QString("New Region %1").arg(QString::number(++i));
        iter = allRegionNames.find(candidate);
    }
    return candidate;
}


void Selection::removedMap(UNUSED QString regionName, QString mapName) {
    auto map = getMap();
    if (!map->isValid()) {
        return;
    }
    if (mapName == map->getName()) {
        selectMap(Map::null());
    }
}


void Selection::removedRegion(QString name) {
    auto region = getRegion();
    if (!region->isValid()) {
        return;
    }
    if (name == region->getName()) {
        selectMap(Map::null());
        selectRegion(Region::null());
    }
}


void Selection::setAtlas(QSharedPointer<rpgmapper::model::Atlas> atlas) {
    map = QSharedPointer<rpgmapper::model::Map>{new InvalidMap{}};
    region = QSharedPointer<rpgmapper::model::Region>{new InvalidRegion{}};
    this->atlas = atlas;
    connect(this->atlas.data(), &Atlas::mapRemoved, this, &Selection::removedMap);
    connect(this->atlas.data(), &Atlas::regionRemoved, this, &Selection::removedRegion);
    emit newAtlas();
}


void Selection::selectMap(QSharedPointer<rpgmapper::model::Map> map) {

    this->map = map;
    if (map->isValid()) {
        auto region = getAtlas()->findRegion(map->getRegion()->getName());
        selectRegion(region);
        emit mapSelected(map->getName());
    }
    else {
        emit mapSelected(QString::null);
    }
}


void Selection::selectMap(QString const & mapName) {
    selectMap(atlas->findMap(mapName));
}


void Selection::selectRegion(QSharedPointer<rpgmapper::model::Region> region) {

    this->region = region;
    if (region->isValid()) {
        emit regionSelected(region->getName());
    }
    else {
        emit regionSelected(QString::null);
    }
}


void Selection::selectRegion(QString const & regionName) {
    selectRegion(atlas->findRegion(regionName));
}

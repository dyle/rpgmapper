/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/selection.hpp>

using namespace rpgmapper::model;


Selection::Selection(QObject * parent) : QObject(parent) {
    atlas = AtlasPointer{new InvalidAtlas{}};
    map = MapPointer{new InvalidMap{}};
    region = RegionPointer{new InvalidRegion{}};
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


void Selection::setAtlas(AtlasPointer atlas) {
    this->atlas = atlas;
    emit newAtlas();
}


void Selection::selectMap(MapPointer map) {
    this->map = map;
    auto region = getAtlas()->findRegion(map->getRegion()->getName());
    selectRegion(region);
    emit mapSelected(map->getName());
}


void Selection::selectMap(QString const & mapName) {
    selectMap(atlas->findMap(mapName));
}


void Selection::selectRegion(RegionPointer region) {
    this->region = region;
    emit regionSelected(region->getName());
}


void Selection::selectRegion(QString const & regionName) {
    selectRegion(atlas->findRegion(regionName));
}

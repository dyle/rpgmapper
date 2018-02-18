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


void Selection::setAtlas(AtlasPointer atlas) {
    this->atlas = atlas;
    emit newAtlas();
}


void Selection::selectMap(MapPointer map) {
    if (this->map->getName() != map->getName()) {
        return;
    }
    this->map = map;
    emit mapSelected(map->getName());
}


void Selection::selectMap(QString const & mapName) {
    selectMap(atlas->findMap(mapName));
}


void Selection::selectRegion(RegionPointer region) {
    if (this->region->getName() != region->getName()) {
        return;
    }
    this->region = region;
    emit regionSelected(region->getName());
}


void Selection::selectRegion(QString const & regionName) {
    selectRegion(atlas->findRegion(regionName));
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/resize_map.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


ResizeMap::ResizeMap(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, QSize newSize)
        : AtlasCommand{atlas}, mapName{mapName}, newSize{newSize} {
}


void ResizeMap::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldSize = map->getCoordinateSystem()->getSize();
        map->getCoordinateSystem()->resize(newSize);
    }
}


QString ResizeMap::getDescription() const {
    return QString{"Resize map %1 to %2x%3"}.arg(mapName).arg(newSize.width()).arg(newSize.height());
}


void ResizeMap::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getCoordinateSystem()->resize(oldSize);
    }
}

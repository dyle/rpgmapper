/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


ResizeMap::ResizeMap(QString mapName, QSize newSize) : mapName{std::move(mapName)}, newSize{newSize} {
}


void ResizeMap::execute() {
/**
 * TODO
 *

    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldSize = map->getCoordinateSystem()->getSize();
        map->getCoordinateSystem()->resize(newSize);
    }
*/
}


QString ResizeMap::getDescription() const {
    return QString{"Resize map %1 to %2x%3"}.arg(mapName).arg(newSize.width()).arg(newSize.height());
}


void ResizeMap::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getCoordinateSystem()->resize(oldSize);
    }
*/
}

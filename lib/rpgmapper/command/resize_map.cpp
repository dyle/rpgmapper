/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


ResizeMap::ResizeMap(rpgmapper::model::Map * map, QSize newSize) : map{map}, newSize{newSize} {
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void ResizeMap::execute() {
    oldSize = map->getCoordinateSystem()->getSize();
    map->getCoordinateSystem()->resize(newSize);
}


QString ResizeMap::getDescription() const {
    auto mapName = map->getName();
    return QString{"Resize map %1 to %2x%3"}.arg(mapName).arg(newSize.width()).arg(newSize.height());
}


void ResizeMap::undo() {
    map->getCoordinateSystem()->resize(oldSize);
}

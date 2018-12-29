/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_margin.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapMargin::SetMapMargin(rpgmapper::model::Map * map, float newMargin) : map{map}, newMargin{newMargin} {
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapMargin::execute() {
    oldMargin = map->getCoordinateSystem()->getMargin();
    map->getCoordinateSystem()->setMargin(newMargin);
}


QString SetMapMargin::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set background margins of map %1"}.arg(mapName);
}


void SetMapMargin::undo() {
    map->getCoordinateSystem()->setMargin(oldMargin);
}

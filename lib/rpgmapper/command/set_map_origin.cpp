/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapOrigin::SetMapOrigin(rpgmapper::model::Map * map, CoordinatesOrigin origin) : map{map}, newOrigin{origin} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapOrigin::execute() {
    oldOrigin = map->getCoordinateSystem()->getOrigin();
    map->getCoordinateSystem()->setOrigin(newOrigin);
}


QString SetMapOrigin::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set origin of map %1"}.arg(mapName);
}


void SetMapOrigin::undo() {
    map->getCoordinateSystem()->setOrigin(oldOrigin);
}

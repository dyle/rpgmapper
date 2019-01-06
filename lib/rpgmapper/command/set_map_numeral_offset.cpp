/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_numeral_offset.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapNumeralOffset::SetMapNumeralOffset(rpgmapper::model::Map * map, QPointF newOffset)
        : map{map},
          newOffset{newOffset} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapNumeralOffset::execute() {
    oldOffset = map->getCoordinateSystem()->getOffset();
    map->getCoordinateSystem()->setOffset(newOffset);
}


QString SetMapNumeralOffset::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set coordinate offset map (%1, %2)"}.arg(mapName).arg(newOffset.x()).arg(newOffset.y());
}


void SetMapNumeralOffset::undo() {
    map->getCoordinateSystem()->setOffset(oldOffset);
}

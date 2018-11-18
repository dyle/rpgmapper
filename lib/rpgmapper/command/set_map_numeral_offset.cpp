/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_numeral_offset.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapNumeralOffset::SetMapNumeralOffset(QString mapName, QPointF newOffset)
        : mapName{std::move(mapName)}, newOffset{newOffset} {
}


void SetMapNumeralOffset::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldOffset = map->getCoordinateSystem()->getOffset();
    map->getCoordinateSystem()->setOffset(newOffset);
}


QString SetMapNumeralOffset::getDescription() const {
    return QString{"Set coordinate offset map (%1, %2)"}.arg(mapName).arg(newOffset.x()).arg(newOffset.y());
}


void SetMapNumeralOffset::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    map->getCoordinateSystem()->setOffset(oldOffset);
}

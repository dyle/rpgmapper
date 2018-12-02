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


SetMapMargin::SetMapMargin(QString mapName, float newMargin)
    : mapName{std::move(mapName)}, newMargin{newMargin} {
}


void SetMapMargin::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldMargin = map->getCoordinateSystem()->getMargin();
    map->getCoordinateSystem()->setMargin(newMargin);
}


QString SetMapMargin::getDescription() const {
    return QString{"Set background margins of map %1"}.arg(mapName);
}


void SetMapMargin::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    map->getCoordinateSystem()->setMargin(oldMargin);
}

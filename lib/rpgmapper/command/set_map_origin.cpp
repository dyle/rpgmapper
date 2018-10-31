/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapOrigin::SetMapOrigin(QString mapName, CoordinatesOrigin origin)
        : mapName{std::move(mapName)}, newOrigin{origin} {
}


void SetMapOrigin::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldOrigin = map->getCoordinateSystem()->getOrigin();
    map->getCoordinateSystem()->setOrigin(newOrigin);
}


QString SetMapOrigin::getDescription() const {
    return QString{"Set origin of map %1"}.arg(mapName);
}


void SetMapOrigin::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    map->getCoordinateSystem()->setOrigin(oldOrigin);
}

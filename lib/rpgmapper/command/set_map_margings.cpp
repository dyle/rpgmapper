/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_margins.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapMargins::SetMapMargins(QString mapName, QMargins newMargins)
    : mapName{std::move(mapName)}, newMargins{newMargins} {
}


void SetMapMargins::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldMargins = map->getLayers().getBackgroundLayer()->getMargins();
    map->getLayers().getBackgroundLayer()->setMargins(newMargins);
}


QString SetMapMargins::getDescription() const {
    return QString{"Set background margins of map %1"}.arg(mapName);
}


void SetMapMargins::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    map->getLayers().getBackgroundLayer()->setMargins(oldMargins);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_rendering.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundRendering::SetMapBackgroundRendering(QString mapName, QString newRendering)
    : mapName{std::move(mapName)}, newRendering{std::move(newRendering)} {
}


void SetMapBackgroundRendering::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldRendering = map->getLayers().getBackgroundLayer()->getRendering();
    map->getLayers().getBackgroundLayer()->setRendering(newRendering);
}


QString SetMapBackgroundRendering::getDescription() const {
    return QString{"Set background rendering of map %1 to %2"}.arg(mapName).arg(newRendering);
}


void SetMapBackgroundRendering::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    map->getLayers().getBackgroundLayer()->setRendering(oldRendering);
}

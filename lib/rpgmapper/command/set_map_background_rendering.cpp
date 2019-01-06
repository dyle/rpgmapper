/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_rendering.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundRendering::SetMapBackgroundRendering(rpgmapper::model::Map * map, QString newRendering)
    : map{map},
      newRendering{std::move(newRendering)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapBackgroundRendering::execute() {
    oldRendering = map->getLayers().getBackgroundLayer()->getRendering();
    map->getLayers().getBackgroundLayer()->setRendering(newRendering);
}


QString SetMapBackgroundRendering::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set background rendering of map %1 to %2"}.arg(mapName).arg(newRendering);
}


void SetMapBackgroundRendering::undo() {
    map->getLayers().getBackgroundLayer()->setRendering(oldRendering);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_image_render_mode.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;
using namespace rpgmapper::model::layer;


SetMapBackgroundImageRenderMode::SetMapBackgroundImageRenderMode(rpgmapper::model::Map * map, ImageRenderMode newMode)
    : map{map},
      newMode{newMode},
      oldMode{ImageRenderMode::plain} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapBackgroundImageRenderMode::execute() {
    oldMode = map->getLayers().getBackgroundLayer()->getImageRenderMode();
    map->getLayers().getBackgroundLayer()->setImageRenderMode(newMode);
}


QString SetMapBackgroundImageRenderMode::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set background image rendering of map %1 to %2"}.arg(mapName).arg(imageRenderModeToString(newMode));
}


void SetMapBackgroundImageRenderMode::undo() {
    map->getLayers().getBackgroundLayer()->setImageRenderMode(oldMode);
}

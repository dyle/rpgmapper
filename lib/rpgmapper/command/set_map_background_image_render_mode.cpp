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


SetMapBackgroundImageRenderMode::SetMapBackgroundImageRenderMode(QString mapName,
                                                                 rpgmapper::model::ImageRenderMode newMode)
    : mapName{std::move(mapName)}, newMode{newMode}, oldMode{ImageRenderMode::plain} {
}


void SetMapBackgroundImageRenderMode::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldMode = map->getLayers().getBackgroundLayer()->getImageRenderMode();
    map->getLayers().getBackgroundLayer()->setImageRenderMode(newMode);
}


QString SetMapBackgroundImageRenderMode::getDescription() const {
    return QString{"Set background image rendering of map %1 to %2"}.arg(mapName).arg(imageRenderModeToString(newMode));
}


void SetMapBackgroundImageRenderMode::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    map->getLayers().getBackgroundLayer()->setImageRenderMode(oldMode);
}

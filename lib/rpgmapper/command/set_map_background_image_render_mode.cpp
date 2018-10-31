/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_image_render_mode.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundImageRenderMode::SetMapBackgroundImageRenderMode(QString mapName,
                                                                 rpgmapper::model::ImageRenderMode newMode)
    : mapName{std::move(mapName)}, newMode{newMode}, oldMode{ImageRenderMode::plain} {
}


void SetMapBackgroundImageRenderMode::execute() {
/**
 * TODO
 *

    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldMode = map->getBackgroundLayer()->getImageRenderMode();
        map->getBackgroundLayer()->setImageRenderMode(newMode);
    }
*/
}


QString SetMapBackgroundImageRenderMode::getDescription() const {
    return QString{"Set background image rendering of map %1 to %2"}.arg(mapName).arg(imageRenderModeToString(newMode));
}


void SetMapBackgroundImageRenderMode::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getBackgroundLayer()->setImageRenderMode(oldMode);
    }
*/
}

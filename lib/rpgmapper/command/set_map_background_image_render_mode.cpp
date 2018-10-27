/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_background_image_render_mode.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundImageRenderMode::SetMapBackgroundImageRenderMode(QSharedPointer<rpgmapper::model::Atlas> & atlas,
                                                                 QString const & mapName,
                                                                 rpgmapper::model::ImageRenderMode newMode)
    : AtlasCommand{atlas}, mapName{mapName}, newMode{newMode}, oldMode{ImageRenderMode::plain} {
}


void SetMapBackgroundImageRenderMode::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldMode = map->getBackgroundLayer()->getImageRenderMode();
        map->getBackgroundLayer()->setImageRenderMode(newMode);
    }
}


QString SetMapBackgroundImageRenderMode::getDescription() const {
    return QString{"Set background image rendering of map %1 to %2"}.arg(mapName).arg(imageRenderModeToString(newMode));
}


void SetMapBackgroundImageRenderMode::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getBackgroundLayer()->setImageRenderMode(oldMode);
    }
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_background_rendering.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundRendering::SetMapBackgroundRendering(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, QString newRendering)
    : AtlasCommand{atlas}, mapName{mapName}, newRendering{newRendering} {
}


void SetMapBackgroundRendering::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldRendering = map->getBackgroundLayer()->getRendering();
        map->getBackgroundLayer()->setRendering(newRendering);
    }
}


QString SetMapBackgroundRendering::getDescription() const {
    return QString{"Set background rendering of map %1 to %2"}.arg(mapName).arg(newRendering);
}


void SetMapBackgroundRendering::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getBackgroundLayer()->setRendering(oldRendering);
    }
}

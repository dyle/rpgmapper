/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_map_margins.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapMargins::SetMapMargins(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, QMargins newMargins)
    : AtlasCommand{atlas}, mapName{mapName}, newMargins{newMargins} {
}


void SetMapMargins::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldMargins = map->getBackgroundLayer()->getMargins();
        map->getBackgroundLayer()->setMargins(newMargins);
    }
}


QString SetMapMargins::getDescription() const {
    return QString{"Set background margins of map %1"}.arg(mapName);
}


void SetMapMargins::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getBackgroundLayer()->setMargins(oldMargins);
    }
}

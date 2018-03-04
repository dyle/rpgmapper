/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_grid_color.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapGridColor::SetMapGridColor(AtlasPointer & atlas, QString const & mapName, QColor newColor)
    : AtlasCommand{atlas}, mapName{mapName}, newColor{newColor} {
}


void SetMapGridColor::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldColor = map->getGridLayer()->getGridColor();
        map->getGridLayer()->setGridColor(newColor);
    }
}


QString SetMapGridColor::getDescription() const {
    return QString{"Set grid color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapGridColor::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getGridLayer()->setGridColor(oldColor);
    }
}

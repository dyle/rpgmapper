#include <utility>

#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapGridColor::SetMapGridColor(QString mapName, QColor newColor)
    : mapName{std::move(mapName)}, newColor{std::move(newColor)} {
}


void SetMapGridColor::execute() {
/**
 * TODO
 *

    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldColor = map->getGridLayer()->getColor();
        map->getGridLayer()->setColor(newColor);
    }
*/
}


QString SetMapGridColor::getDescription() const {
    return QString{"Set grid color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapGridColor::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getGridLayer()->setColor(oldColor);
    }
*/
}

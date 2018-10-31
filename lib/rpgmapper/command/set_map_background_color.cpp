/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_color.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundColor::SetMapBackgroundColor(QString mapName, QColor newColor)
    : mapName{std::move(mapName)}, newColor{std::move(newColor)} {
}


void SetMapBackgroundColor::execute() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldColor = map->getBackgroundLayer()->getColor();
        map->getBackgroundLayer()->setColor(newColor);
    }
*/
}


QString SetMapBackgroundColor::getDescription() const {
    return QString{"Set background color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapBackgroundColor::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getBackgroundLayer()->setColor(oldColor);
    }
*/
}

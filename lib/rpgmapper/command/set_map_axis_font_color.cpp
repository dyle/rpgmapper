/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_axis_font_color.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapAxisFontColor::SetMapAxisFontColor(QString mapName, QColor newColor)
    : mapName{std::move(mapName)}, newColor{std::move(newColor)} {
}


void SetMapAxisFontColor::execute() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldColor = map->getAxisLayer()->getColor();
        map->getAxisLayer()->setColor(newColor);
    }
*/
}


QString SetMapAxisFontColor::getDescription() const {
    return QString{"Set axis color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapAxisFontColor::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getAxisLayer()->setColor(oldColor);
    }
*/
}

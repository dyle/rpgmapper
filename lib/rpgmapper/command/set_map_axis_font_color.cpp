/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_axis_font_color.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapAxisFontColor::SetMapAxisFontColor(rpgmapper::model::Map * map, QColor newColor)
    : map{map},
      newColor{std::move(newColor)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapAxisFontColor::execute() {
    oldColor = map->getLayers().getAxisLayer()->getColor();
    map->getLayers().getAxisLayer()->setColor(newColor);
}


QString SetMapAxisFontColor::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set axis color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapAxisFontColor::undo() {
    map->getLayers().getAxisLayer()->setColor(oldColor);
}

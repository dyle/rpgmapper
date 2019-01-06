/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_color.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundColor::SetMapBackgroundColor(rpgmapper::model::Map * map, QColor newColor)
    : map{map},
      newColor{std::move(newColor)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapBackgroundColor::execute() {
    oldColor = map->getLayers().getBackgroundLayer()->getColor();
    map->getLayers().getBackgroundLayer()->setColor(newColor);
}


QString SetMapBackgroundColor::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set background color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapBackgroundColor::undo() {
    map->getLayers().getBackgroundLayer()->setColor(oldColor);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapGridColor::SetMapGridColor(rpgmapper::model::Map * map, QColor newColor)
    : map{map},
      newColor{std::move(newColor)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapGridColor::execute() {
    oldColor = map->getLayers().getGridLayer()->getColor();
    map->getLayers().getGridLayer()->setColor(newColor);
}


QString SetMapGridColor::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set grid color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapGridColor::undo() {
    map->getLayers().getGridLayer()->setColor(oldColor);
}

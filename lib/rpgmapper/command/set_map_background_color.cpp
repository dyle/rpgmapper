/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_color.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundColor::SetMapBackgroundColor(QString mapName, QColor newColor)
    : mapName{std::move(mapName)}, newColor{std::move(newColor)} {
}


void SetMapBackgroundColor::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }

    oldColor = map->getLayers().getBackgroundLayer()->getColor();
    map->getLayers().getBackgroundLayer()->setColor(newColor);
}


QString SetMapBackgroundColor::getDescription() const {
    return QString{"Set background color of map %1 to %2"}.arg(mapName).arg(newColor.name(QColor::HexArgb));
}


void SetMapBackgroundColor::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    map->getLayers().getBackgroundLayer()->setColor(oldColor);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_axis_font.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapAxisFont::SetMapAxisFont(QString mapName, QFont newFont) : mapName{std::move(mapName)}, newFont{newFont} {
}


void SetMapAxisFont::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldFont = map->getLayers().getAxisLayer()->getFont();
    map->getLayers().getAxisLayer()->setFont(newFont);
}


QString SetMapAxisFont::getDescription() const {
    return QString{"Set axis font of map %1 to %2 %3pt"}.arg(mapName).arg(newFont.family()).arg(newFont.pointSize());
}


void SetMapAxisFont::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    map->getLayers().getAxisLayer()->setFont(oldFont);
}

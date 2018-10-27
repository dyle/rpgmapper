/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_axis_font.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapAxisFont::SetMapAxisFont(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, QFont newFont)
    : AtlasCommand{atlas}, mapName{mapName}, newFont{newFont} {
}


void SetMapAxisFont::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldFont = map->getAxisLayer()->getFont();
        map->getAxisLayer()->setFont(newFont);
    }
}


QString SetMapAxisFont::getDescription() const {
    return QString{"Set axis font of map %1 to %2 %3pt"}.arg(mapName).arg(newFont.family()).arg(newFont.pointSize());
}


void SetMapAxisFont::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getAxisLayer()->setFont(oldFont);
    }
}

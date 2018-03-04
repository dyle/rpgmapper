/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_numeral_offset.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapNumeralOffset::SetMapNumeralOffset(AtlasPointer & atlas, QString const & mapName, QPointF newOffset)
        : AtlasCommand{atlas}, mapName{mapName}, newOffset{newOffset} {
}


void SetMapNumeralOffset::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldOffset = map->getCoordinateSystem().getOffsetF();
        map->setCoordinateOffset(newOffset);
    }
}


QString SetMapNumeralOffset::getDescription() const {
    return QString{"Set coordinate offset map (%1, %2)"}.arg(mapName).arg(newOffset.x()).arg(newOffset.y());
}


void SetMapNumeralOffset::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->setCoordinateOffset(oldOffset);
    }
}

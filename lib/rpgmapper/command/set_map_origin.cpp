/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_origin.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapOrigin::SetMapOrigin(AtlasPointer & atlas, QString const & mapName, CoordinatesOrigin origin)
        : AtlasCommand{atlas}, mapName{mapName}, newOrigin{origin} {
}


void SetMapOrigin::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldOrigin = map->getCoordinateSystem().getOrigin();
        map->setOrigin(newOrigin);
    }
}


QString SetMapOrigin::getDescription() const {
    return QString{"Set origin of map %1"}.arg(mapName);
}


void SetMapOrigin::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->setOrigin(oldOrigin);
    }
}

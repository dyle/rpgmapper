/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/remove_map.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveMap::RemoveMap(AtlasPointer & atlas,
                     QString const & regionName,
                     QString const & mapName):
                            AtlasCommand{atlas}, mapName{mapName}, regionName{regionName} {
}

void RemoveMap::execute() {
    auto atlas = getAtlas();
    auto region = atlas->findRegion(regionName);
    if (region->isValid()) {
        region->removeMap(mapName);
    }
}

QString RemoveMap::getDescription() const {
    return QString{"Remove map %1 from region %2."}.arg(mapName).arg(regionName);
}

void RemoveMap::undo() {
    auto atlas = getAtlas();
    auto region = atlas->findRegion(regionName);
    if (region->isValid()) {
        region->createMap(mapName);
    }
}

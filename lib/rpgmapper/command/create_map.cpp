/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/create_map.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


CreateMap::CreateMap(QString const & regionName,
                     QString const & mapName):
                            AtlasCommand{atlas}, mapName{mapName}, regionName{regionName} {
}


void CreateMap::execute() {
    auto atlas = getAtlas();
    auto region = atlas->findRegion(regionName);
    if (region->isValid()) {
        region->createMap(mapName);
    }
}


QString CreateMap::getDescription() const {
    return QString{"Create map %1 in region %2."}.arg(mapName).arg(regionName);
}


void CreateMap::undo() {
    auto atlas = getAtlas();
    auto region = atlas->findRegion(regionName);
    if (region->isValid()) {
        region->removeMap(mapName);
    }
}

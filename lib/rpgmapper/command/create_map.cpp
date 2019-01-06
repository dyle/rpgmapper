/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/create_map.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


CreateMap::CreateMap(QString regionName, QString mapName)
    : mapName{std::move(mapName)},
      regionName{std::move(regionName)} {
}


void CreateMap::execute() {
    
    auto session = Session::getCurrentSession();
    
    auto presentMap = session->findMap(mapName);
    if (presentMap->isValid()) {
        throw exception::invalid_mapname{};
    }
    
    auto region = session->findRegion(regionName);
    if (region->isValid()) {
        
        if (!map) {
            map = MapPointer{new Map{mapName}};
        }
        region->addMap(map);
    }
    else {
        throw exception::invalid_region{};
    }
}


QString CreateMap::getDescription() const {
    return QString{"Create map %1 in region %2."}.arg(mapName).arg(regionName);
}


void CreateMap::undo() {
    
    auto session = Session::getCurrentSession();
    auto region = session->findRegion(regionName);
    if (!region->isValid()) {
        throw exception::invalid_region{};
    }
    
    region->removeMap(mapName);
}

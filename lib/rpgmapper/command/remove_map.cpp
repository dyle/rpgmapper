/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveMap::RemoveMap(rpgmapper::model::Map * map) : map{map} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    auto session = Session::getCurrentSession();
    removedMap = session->findMap(map->getName());
    
    auto regionName = session->getAllMapNames()[map->getName()];
    region = session->findRegion(regionName).data();
    
    if (!region || !region->isValid()) {
        throw rpgmapper::model::exception::invalid_region();
    }
}


void RemoveMap::execute() {
    region->removeMap(map->getName());
}


QString RemoveMap::getDescription() const {
    auto mapName = map->getName();
    auto regionName = region->getName();
    return QString{"Remove map %1 from region %2."}.arg(mapName).arg(regionName);
}


void RemoveMap::undo() {
    region->addMap(removedMap);
}

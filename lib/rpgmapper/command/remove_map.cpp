/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveMap::RemoveMap(QString mapName) {
    
    auto session = Session::getCurrentSession();
    map = session->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    regionName = session->getAllMapNames()[mapName];
}


void RemoveMap::execute() {
    
    auto session = Session::getCurrentSession();
    auto region = session->findRegion(regionName);
    if (!region->isValid()) {
        throw exception::invalid_region;
    }
    
    region->removeMap(map->getName());
}


QString RemoveMap::getDescription() const {
    return QString{"Remove map %1 from region %2."}.arg(map->getName()).arg(regionName);
}


void RemoveMap::undo() {
    auto session = Session::getCurrentSession();
    session->insertMap(map);
    session->findRegion(regionName)->addMap(map->getName());
}

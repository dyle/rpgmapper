#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveMap::RemoveMap(QString regionName, QString mapName)
    : mapName{std::move(mapName)}, regionName{std::move(regionName)} {
}


void RemoveMap::execute() {
/**
 * TODO
 *
    auto session = Session::getCurrentSession();
    auto region = session->findRegion(regionName);
    if (region->isValid()) {
        region->removeMap(mapName);
    }
*/
}


QString RemoveMap::getDescription() const {
    return QString{"Remove map %1 from region %2."}.arg(mapName).arg(regionName);
}


void RemoveMap::undo() {
/**
 * TODO
 *
    auto session = Session::getCurrentSession();
    auto region = atlas->findRegion(regionName);
    if (region->isValid()) {
        region->createMap(mapName);
    }
*/
}

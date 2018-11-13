/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


ResizeMap::ResizeMap(QString mapName, QSize newSize) : mapName{std::move(mapName)}, newSize{newSize} {
}


void ResizeMap::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    oldSize = map->getCoordinateSystem()->getSize();
    map->getCoordinateSystem()->resize(newSize);
}


QString ResizeMap::getDescription() const {
    return QString{"Resize map %1 to %2x%3"}.arg(mapName).arg(newSize.width()).arg(newSize.height());
}


void ResizeMap::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    map->getCoordinateSystem()->resize(oldSize);
}

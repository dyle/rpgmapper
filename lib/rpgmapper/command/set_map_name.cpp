/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapName::SetMapName(rpgmapper::model::Map * map, QString newName)
        : map{map}, newName{std::move(newName)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapName::execute() {
    oldName = map->getName();
    map->setName(newName);
}


QString SetMapName::getDescription() const {
    return QString{"Set name of map %1 to %2."}.arg(oldName).arg(newName);
}


void SetMapName::undo() {
    map->setName(oldName);
}

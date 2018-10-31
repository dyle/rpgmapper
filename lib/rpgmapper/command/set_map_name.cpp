/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapName::SetMapName(QString oldName, QString newName)
        : newName{std::move(newName)}, oldName{std::move(oldName)} {
}


void SetMapName::execute() {
    
    auto map = Session::getCurrentSession()->findMap(oldName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    map->setName(newName);
}


QString SetMapName::getDescription() const {
    return QString{"Set name of map %1 to %2."}.arg(oldName).arg(newName);
}


void SetMapName::undo() {
    
    auto map = Session::getCurrentSession()->findMap(newName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    map->setName(oldName);
}

#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapName::SetMapName(QString oldName, QString newName)
        : newName{std::move(newName)}, oldName{std::move(oldName)} {
}


void SetMapName::execute() {
/**
 * TODO
 *

    auto atlas = getAtlas();
    auto map = atlas->findMap(oldName);
    if (!map->isValid()) {
        return;
    }

    if (!Map::isNameValid(newName)) {
        throw std::runtime_error("Map name is invalid.");
    }
    if (atlas->findMap(newName)->isValid()) {
        throw std::runtime_error("Map with new name already exists.");
    }

    map->setName(newName);
*/
}


QString SetMapName::getDescription() const {
    return QString{"Set name of map %1 to %2."}.arg(oldName).arg(newName);
}


void SetMapName::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(newName);
    if (!map->isValid()) {
        return;
    }
    map->setName(oldName);
*/
}

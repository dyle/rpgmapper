/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_name.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapName::SetMapName(AtlasPointer & atlas, QString const & oldName, QString const & newName)
        : AtlasCommand{atlas}, newName{newName}, oldName{oldName} {
}


void SetMapName::execute() {

    auto atlas = getAtlas();
    auto map = atlas->findMap(oldName);
    if (!map->isValid()) {
        return;
    }

    // TODO: check for existing name
    // TODO: check for invalid characters

    map->setName(newName);
}


QString SetMapName::getDescription() const {
    return QString{"Set name of map %1 to %2."}.arg(oldName).arg(newName);
}


void SetMapName::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(newName);
    if (!map->isValid()) {
        return;
    }
    map->setName(oldName);
}

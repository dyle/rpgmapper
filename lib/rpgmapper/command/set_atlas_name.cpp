#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_atlas_name.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetAtlasName::SetAtlasName(QString name) : newName{std::move(name)} {
}


void SetAtlasName::execute() {
/**
 * TODO
 *

    if (!Atlas::isNameValid(newName)) {
        throw std::runtime_error("Atlas name is invalid.");
    }

    auto atlas = getAtlas();
    oldName = atlas->getName();
    atlas->setName(newName);
*/
}


QString SetAtlasName::getDescription() const {
    return QString{"Set atlas name to %1."}.arg(newName);
}


void SetAtlasName::undo() {
/**
 * TODO
 *

    auto atlas = getAtlas();
    atlas->setName(oldName);
*/
}

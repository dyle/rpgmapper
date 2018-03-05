/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_atlas_name.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetAtlasName::SetAtlasName(AtlasPointer & atlas, QString const & name): AtlasCommand{atlas}, newName{name} {
}


void SetAtlasName::execute() {

    if (!Atlas::isNameValid(newName)) {
        throw std::runtime_error("Atlas name is invalid.");
    }

    auto atlas = getAtlas();
    oldName = atlas->getName();
    atlas->setName(newName);
}


QString SetAtlasName::getDescription() const {
    return QString{"Set atlas name to %1."}.arg(newName);
}


void SetAtlasName::undo() {
    auto atlas = getAtlas();
    atlas->setName(oldName);
}

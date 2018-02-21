/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/atlas_set_name.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


AtlasSetName::AtlasSetName(AtlasPointer & atlas, QString const & name): AtlasCommand{atlas}, newName{name} {
}

void AtlasSetName::execute() {
    auto atlas = getAtlas();
    oldName = atlas->getName();
    atlas->setName(newName);
}

QString AtlasSetName::getDescription() const {
    return QString{"Set atlas name to %1."}.arg(newName);
}

void AtlasSetName::undo() {
    auto atlas = getAtlas();
    atlas->setName(oldName);
}

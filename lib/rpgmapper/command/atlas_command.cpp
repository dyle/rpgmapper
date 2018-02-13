/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/atlas_command.hpp>

using namespace rpgmapper::model::command;


AtlasPointer AtlasCommand::getAtlas() {
    auto atlas = this->atlas.toStrongRef();
    if (atlas.isNull()) {
        throw std::runtime_error("Atlas for atlas command is nullptr.");
    }
    return atlas;
}


AtlasPointer const AtlasCommand::getAtlas() const {
    auto atlas = this->atlas.toStrongRef();
    if (atlas.isNull()) {
        throw std::runtime_error("Atlas for atlas command is nullptr.");
    }
    return atlas;
}

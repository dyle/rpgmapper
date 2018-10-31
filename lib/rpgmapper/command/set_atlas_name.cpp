/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_atlas_name.hpp>
#include <rpgmapper/exception/invalid_atlas.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetAtlasName::SetAtlasName(QString name) : newName{std::move(name)} {
}


void SetAtlasName::execute() {
    
    auto atlas = Session::getCurrentSession()->getAtlas();
    if (!atlas->isValid()) {
        throw rpgmapper::model::exception::invalid_atlas();
    }
    
    oldName = atlas->getName();
    atlas->setName(newName);
}


QString SetAtlasName::getDescription() const {
    return QString{"Set atlas name to %1."}.arg(newName);
}


void SetAtlasName::undo() {
    
    auto atlas = Session::getCurrentSession()->getAtlas();
    if (!atlas->isValid()) {
        throw rpgmapper::model::exception::invalid_atlas();
    }
    atlas->setName(oldName);
}

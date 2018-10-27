/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_region_name.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetRegionName::SetRegionName(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & oldName, QString const & newName)
        : AtlasCommand{atlas}, newName{newName}, oldName{oldName} {
}


void SetRegionName::execute() {

    auto atlas = getAtlas();
    auto region = atlas->findRegion(oldName);
    if (!region->isValid()) {
        return;
    }

    if (!Region::isNameValid(newName)) {
        throw std::runtime_error("Region name is invalid.");
    }
    if (atlas->findRegion(newName)->isValid()) {
        throw std::runtime_error("Region with new name already exists.");
    }

    region->setName(newName);
}


QString SetRegionName::getDescription() const {
    return QString{"Set name of region %1 to %2."}.arg(oldName).arg(newName);
}


void SetRegionName::undo() {
    auto atlas = getAtlas();
    auto region = atlas->findRegion(newName);
    if (!region->isValid()) {
        return;
    }
    region->setName(oldName);
}

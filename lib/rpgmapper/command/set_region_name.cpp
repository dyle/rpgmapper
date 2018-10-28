/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_region_name.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetRegionName::SetRegionName(QString oldName, QString newName)
        : newName{std::move(newName)}, oldName{std::move(oldName)} {
}


void SetRegionName::execute() {
/**
 * TODO
 *
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
*/
}


QString SetRegionName::getDescription() const {
    return QString{"Set name of region %1 to %2."}.arg(oldName).arg(newName);
}


void SetRegionName::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto region = atlas->findRegion(newName);
    if (!region->isValid()) {
        return;
    }
    region->setName(oldName);
*/
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_region_name.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetRegionName::SetRegionName(rpgmapper::model::Region * region, QString newName)
    : region{region},
      newName{std::move(newName)} {
    
    if (!region || !region->isValid()) {
        throw rpgmapper::model::exception::invalid_region{};
    }
}


void SetRegionName::execute() {
    oldName = region->getName();
    region->setName(newName);
}


QString SetRegionName::getDescription() const {
    return QString{"Set name of region %1 to %2."}.arg(oldName).arg(newName);
}


void SetRegionName::undo() {
    region->setName(oldName);
}

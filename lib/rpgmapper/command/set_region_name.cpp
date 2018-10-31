/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/set_region_name.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetRegionName::SetRegionName(QString oldName, QString newName)
        : newName{std::move(newName)}, oldName{std::move(oldName)} {
}


void SetRegionName::execute() {
    
    auto region = Session::getCurrentSession()->findRegion(oldName);
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    region->setName(newName);
}


QString SetRegionName::getDescription() const {
    return QString{"Set name of region %1 to %2."}.arg(oldName).arg(newName);
}


void SetRegionName::undo() {
    
    auto region = Session::getCurrentSession()->findRegion(newName);
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    region->setName(oldName);
}

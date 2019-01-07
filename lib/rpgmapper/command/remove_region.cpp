/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/remove_region.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveRegion::RemoveRegion(rpgmapper::model::Region * region) : region{region} {
    
    if (!region || !region->isValid()) {
        throw rpgmapper::model::exception::invalid_region();
    }
    
    auto session = Session::getCurrentSession();
    removedRegion = session->findRegion(region->getName());
}


void RemoveRegion::execute() {
    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();
    atlas->removeRegion(region->getName());
}


QString RemoveRegion::getDescription() const {
    return QString{"Remove region %1."}.arg(region->getName());
}


void RemoveRegion::undo() {
    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();
    atlas->addRegion(removedRegion);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/create_region.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


CreateRegion::CreateRegion(QString name): name{std::move(name)} {
}


void CreateRegion::execute() {
    
    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();
    auto region = session->findRegion(name);
    if (region->isValid()) {
        throw exception::invalid_regionname{};
    }

    region = RegionPointer{new Region{name}};
    atlas->addRegion(region);
}


QString CreateRegion::getDescription() const {
    return QString{"Create region %1."}.arg(name);
}


void CreateRegion::undo() {
    auto session = Session::getCurrentSession();
    auto region = session->findRegion(name);
    if (!region->isValid()) {
        throw exception::invalid_region{};
    }
    
    auto atlas = session->getAtlas();
    atlas->removeRegion(name);
}

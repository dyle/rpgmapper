/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/remove_region.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveRegion::RemoveRegion(QString name) {
    region = Session::getCurrentSession()->findRegion(std::move(name));
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
}


void RemoveRegion::execute() {

    auto session = Session::getCurrentSession();
    for (auto const & mapName : region->getMapNames()) {
        maps.insert(session->findMap(mapName));
    }

    session->deleteRegion(region->getName());
}


QString RemoveRegion::getDescription() const {
    return QString{"Remove region %1."}.arg(region->getName());
}


void RemoveRegion::undo() {
    
    auto session = Session::getCurrentSession();
    session->insertRegion(region);
    for (auto const & map : maps) {
        session->insertMap(map);
        map->setRegionName(region->getName());
    }
}

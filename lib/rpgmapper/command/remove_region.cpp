/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/command/remove_region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveRegion::RemoveRegion(QString regionName) : regionName{std::move(regionName)} {
}


void RemoveRegion::execute() {

    clearCommands();

    auto session = Session::getCurrentSession();
    auto region = session->findRegion(regionName);
    for (auto const & mapName : region->getMapNames()) {
        addCommand(QSharedPointer<rpgmapper::model::command::Command>{new RemoveMap{regionName, mapName}});
    }
    CompositeCommand::execute();

    session->removeRegion(regionName);
}


QString RemoveRegion::getDescription() const {
    return QString{"Remove region %1."}.arg(regionName);
}


void RemoveRegion::undo() {
/**
 * TODO
 *

    auto atlas = getAtlas();
    auto region = atlas->createRegion(regionName);
    CompositeCommand::undo();
*/
}

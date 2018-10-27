/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/command/remove_region.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


RemoveRegion::RemoveRegion(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & regionName):
        CompositeCommand{atlas}, regionName{regionName} {
}


void RemoveRegion::execute() {

    clearCommands();

    auto atlas = getAtlas();
    auto region = atlas->findRegion(regionName);

    for (auto const & pair : region->getMaps()) {
        addCommand(QSharedPointer<rpgmapper::model::command::Command>{new RemoveMap{atlas, regionName, pair.second->getName()}});
    }
    CompositeCommand::execute();

    atlas->removeRegion(regionName);
}


QString RemoveRegion::getDescription() const {
    return QString{"Remove region %1."}.arg(regionName);
}


void RemoveRegion::undo() {

    auto atlas = getAtlas();
    auto region = atlas->createRegion(regionName);
    CompositeCommand::undo();
}

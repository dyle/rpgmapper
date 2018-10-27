/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/create_region.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


CreateRegion::CreateRegion(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & name): AtlasCommand{atlas}, name{name} {
}


void CreateRegion::execute() {
    auto atlas = getAtlas();
    atlas->createRegion(name);
}


QString CreateRegion::getDescription() const {
    return QString{"Create region %1."}.arg(name);
}


void CreateRegion::undo() {
    auto atlas = getAtlas();
    atlas->removeRegion(name);
}

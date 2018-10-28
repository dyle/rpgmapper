#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/create_region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


CreateRegion::CreateRegion(QString name): name{std::move(name)} {
}


void CreateRegion::execute() {
    auto session = Session::getCurrentSession();
    session->createRegion(name);
}


QString CreateRegion::getDescription() const {
    return QString{"Create region %1."}.arg(name);
}


void CreateRegion::undo() {
    auto session = Session::getCurrentSession();
    session->deleteRegion(name);
}

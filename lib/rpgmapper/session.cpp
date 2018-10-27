/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


Session::Session(QObject * parent)
        : QObject(parent) {
    
}


void Session::selectMap(QSharedPointer<rpgmapper::model::Map> map) {
    currentMap = map;
    emit mapSelected(currentMap->getName());
}


void Session::selectMap(QString const & mapName) {
    // TODO
}


void Session::selectRegion(QSharedPointer<rpgmapper::model::Region> region) {
    currentRegion = region;
    emit regionSelected(currentRegion->getName());
}


void Session::selectRegion(QString const & regionName) {
    // TODO
}

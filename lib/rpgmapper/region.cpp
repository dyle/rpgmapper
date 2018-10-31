/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


Region::Region(QString name) : Nameable{} {
    setName(name);
}


void Region::addMap(QString name) {
    
    if (maps.find(name) != maps.end()) {
        return;
    }
    
    auto map = Session::getCurrentSession()->findMap(name);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }

    emit mapAdded(name);
}


bool Region::applyJSON(QJsonObject const & json) {
    // TODO
    return true;
}


QString Region::createRegionName() {

}


QJsonObject Region::getJSON() const {
    // TODO
    return QJsonObject();
}


QSharedPointer<rpgmapper::model::Region> const & Region::null() {
    static QSharedPointer<rpgmapper::model::Region> nullRegion{new InvalidRegion};
    return nullRegion;
}


void Region::removeMap(QString mapName) {
    
    auto map = maps.find(mapName);
    
    if (map != maps.end()) {
        return;
    }
    
    maps.erase(map);
    emit mapRemoved(mapName);
}


void Region::setName(QString name) {
    
    if (name == getName()) {
        return;
    }
    
    auto region = Session::getCurrentSession()->findRegion();
    if (region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    Nameable::setName(name);
}

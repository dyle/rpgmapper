/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/session.hpp>

#include "zip.hpp"

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


/**
 * The one and only current session.
 */
static QSharedPointer<Session> currentSession;


Session::Session()
        : QObject() {
    
}


void Session::changeMapLookup(QString oldName, QString newName) {
    
    auto map = findMap(oldName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    if (findMap(newName)->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    maps[newName] = map;
    maps.erase(oldName);
}


void Session::changeRegionLookup(QString oldName, QString newName) {
    
    auto region = findRegion(oldName);
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    if (findRegion(newName)->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    regions[newName] = region;
    regions.erase(oldName);
}


QSharedPointer<rpgmapper::model::Map> & Session::createMap(QString mapName, QString regionName) {
    
    if (!MapNameValidator::isValid(mapName)) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    auto map = findMap(mapName);
    if (map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    auto region = findRegion(regionName);
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }

    maps.emplace(QSharedPointer<rpgmapper::model::Map>(new Map(mapName, regionName)));
    emit mapCreated(mapName);
    return maps[mapName];
}


QSharedPointer<rpgmapper::model::Region> & Session::createRegion(QString name) {
    
    auto region = findRegion(name);
    if (region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    regions.emplace(QSharedPointer<rpgmapper::model::Region>(new Region(name)));
    emit regionCreated(name);
    return regions[name];
}


void Session::deleteMap(QString mapName) {
    
    auto map = findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_mapname();
    }
    
    auto region = findRegion(map->getRegionName());
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_region();
    }
    
    region->removeMap(mapName);
    maps.erase(mapName);
    emit mapDeleted(mapName);
}


void Session::deleteRegion(QString regionName) {
    
    auto region = findRegion(regionName);
    if (!region->isValid()) {
        throw rpgmapper::model::exception::invalid_regionname();
    }
    
    for (auto mapName : region->getMapNames()) {
        region->removeMap(mapName);
    }
    
    regions.erase(regionName);
    emit regionDeleted(regionName);
}


QSharedPointer<rpgmapper::model::Map> Session::findMap(QString name) {
    
    static QSharedPointer<rpgmapper::model::Map> invalidMap{new InvalidMap};
    
    auto iter = maps.find(name);
    if (iter == maps.end()) {
        return invalidMap;
    }
    return (*iter).second;
}


QSharedPointer<rpgmapper::model::Map> const Session::findMap(QString name) const {
    
    static QSharedPointer<rpgmapper::model::Map> invalidMap{new InvalidMap};
    
    auto iter = maps.find(name);
    if (iter == maps.end()) {
        return invalidMap;
    }
    return (*iter).second;
}


QSharedPointer<rpgmapper::model::Region> & Session::findRegion(QString name) {
    
    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    return (*iter).second;
}


QSharedPointer<rpgmapper::model::Region> const & Session::findRegion(QString name) const {
    
    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    return (*iter).second;
}


std::set<QString> Session::getAllMapNames() const {
    std::set<QString> names;
    for (auto const & iter : maps) { names.insert(iter.first); }
    return names;
}


std::set<QString> Session::getAllRegionNames() const {
    std::set<QString> names;
    for (auto const & iter : regions) { names.insert(iter.first); }
    return names;
}


QSharedPointer<Session> Session::getCurrentSession() {
    return currentSession;
}


QSharedPointer<Session> Session::init() {
    
    auto session = QSharedPointer<Session>(new Session);
    session->atlas->setName(QObject::tr("New Atlas"));
    
    auto regionName = QObject::tr("New Region 1");
    auto mapName = QObject::tr("New Map 1");
    
    session->createRegion(regionName);
    session->createMap(mapName, regionName);
    
    return session;
}


void Session::insertMap(QSharedPointer<Map> map) {
    maps[map->getName()] = map;
    emit mapCreated(map->getName());
}


void Session::insertRegion(QSharedPointer<Region> region) {
    regions[region->getName()] = region;
    emit regionCreated(region->getName());
}


bool Session::load(UNUSED QSharedPointer<Session> & session, UNUSED QFile & file, UNUSED QStringList & log) {
    // TODO:
    return false;
}


bool Session::save(UNUSED QFile & file, QStringList & log) {
    
    bool written = false;
    if (!atlas->isValid()) {
        written = false;
        log.append("Atlas not valid, refusing to save.");
    }
/**
 * TODO
 *
    else {
        written = writeAtlas(atlas, file, log);
        if (written) {
            atlas->setFileName(file.fileName());
        }
    }
*/
    return written;
}

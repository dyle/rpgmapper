/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QDir>
#include <QStandardPaths>

#include <rpgmapper/command/processor.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>
#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/region.hpp>
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
 * Load all found resources under a folder recursively into the database.
 *
 * @param   folder      the root folder of resources.
 * @param   db          the database to fill.
 */
static void loadResources(QDir folder, ResourceDBPointer db);


/**
 * The one and only current session.
 */
static SessionPointer currentSession;


ResourceDBPointer Session::systemResources;          /**< Static class instance. */
ResourceDBPointer Session::userResources;            /**< Static class instance. */


Session::Session() : QObject() {
    
    loadSystemResourceDB();
    loadUserResourceDB();
    
    atlas = AtlasPointer(new Atlas{QString{"New Atlas"}});
    commandProcessor = command::ProcessorPointer{new command::Processor{}};
}


QString Session::createNewMapName() const {
    
    auto allMapNames = getAllMapNames();
    int i = 1;
    QString candidate = QString{"New Map %1"}.arg(QString::number(i));
    
    auto iter = allMapNames.find(candidate);
    while (iter != allMapNames.end()) {
        candidate = QString{"New Map %1"}.arg(QString::number(++i));
        iter = allMapNames.find(candidate);
    }
    
    return candidate;
}


QString Session::createNewRegionName() const {
    
    auto allRegionNames = getAllRegionNames();
    int i = 1;
    QString candidate = QString{"New Region %1"}.arg(QString::number(i));
    
    auto iter = allRegionNames.find(candidate);
    while (iter != allRegionNames.end()) {
        candidate = QString{"New Region %1"}.arg(QString::number(++i));
        iter = allRegionNames.find(candidate);
    }
    
    return candidate;
}


MapPointer Session::findMap(QString name) {
    
    static MapPointer invalidMap{new InvalidMap};
    
    auto const & regions = getAtlas()->getRegions();
    for (auto const & iterRegion : regions) {
        auto region = iterRegion.second;
        auto iterMap = region->getMaps().find(name);
        if (iterMap != region->getMaps().end()) {
            return getAtlas()->getRegion(region->getName())->getMap(name);
        }
    }
    
    return invalidMap;
}


MapPointer const Session::findMap(QString name) const {
    
    static MapPointer invalidMap{new InvalidMap};
    
    auto const & regions = getAtlas()->getRegions();
    for (auto const & iterRegion : regions) {
        auto region = iterRegion.second;
        auto iterMap = region->getMaps().find(name);
        if (iterMap != region->getMaps().end()) {
            return getAtlas()->getRegion(region->getName())->getMap(name);
        }
    }
    
    return invalidMap;
}


RegionPointer Session::findRegion(QString name) {
    
    static RegionPointer invalidRegion{new InvalidRegion};
    
    auto const & regions = getAtlas()->getRegions();
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    
    return getAtlas()->getRegion(name);
}


RegionPointer const Session::findRegion(QString name) const {
    
    static RegionPointer invalidRegion{new InvalidRegion};
    
    auto const & regions = getAtlas()->getRegions();
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    
    return getAtlas()->getRegion(name);
}


std::map<QString, QString> Session::getAllMapNames() const {
    
    std::map<QString, QString> mapNames;
    
    auto const & regions = getAtlas()->getRegions();
    for (auto const & iterRegion : regions) {
        auto region = iterRegion.second;
        auto regionName = region->getName();
        for (auto const & iterMap : region->getMaps()) {
            auto mapName = iterMap.second->getName();
            mapNames[mapName] = regionName;
        }
    }
    
    return mapNames;
}


std::map<QString, std::set<QString>> Session::getAllRegionNames() const {
    
    std::map<QString, std::set<QString>> regionNames;
    
    auto const & regions = getAtlas()->getRegions();
    for (auto const & iterRegion : regions) {
        auto regionName = iterRegion.second->getName();
        regionNames[regionName] = {};
        for (auto const & iterMap : iterRegion.second->getMaps()) {
            auto mapName = iterMap.second->getName();
            regionNames[regionName].insert(mapName);
        }
    }
    
    return regionNames;
}


SessionPointer Session::getCurrentSession() {
    return currentSession;
}


QString Session::getRegionOfMap(QString mapName) const {
    
    QString regionName = QString::null;
    
    auto allMaps = getAllMapNames();
    auto iter = allMaps.find(mapName);
    if (iter != allMaps.end()) {
        regionName = (*iter).second;
    }

    return regionName;
}


SessionPointer Session::init() {
    
    auto session = SessionPointer(new Session);
    auto atlas = session->getAtlas();
    
    auto atlasName = QObject::tr("New Atlas");
    atlas->setName(atlasName);
    
    auto regionName = QObject::tr("New Region 1");
    auto region = RegionPointer{new Region{regionName}};
    atlas->addRegion(region);
    
    auto mapName = QObject::tr("New Map 1");
    auto map = MapPointer{new Map{mapName}};
    region->addMap(map);

    return session;
}


bool Session::isModified() const {
    return getCommandProcessor()->modifications() != 0;
}


bool Session::load(SessionPointer & session, QFile & file, QStringList & log) {
    
    log.clear();
    session = SessionPointer(new Session);
    auto atlas = session->getAtlas();
    
    bool loaded = readAtlas(atlas, file, log);
    if (loaded) {
        session->fileName = file.fileName();
    }
    
    return loaded;
}


void Session::loadSystemResourceDB() {
    
    static bool loaded = false;
    if (loaded) {
        return;
    }
    
    auto locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    for (auto & location : locations) {
        loadResources(location, systemResources);
    }
}


void Session::loadUserResourceDB() {
    
    static bool loaded = false;
    if (loaded) {
        return;
    }
    
    auto locations = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    for (auto & location : locations) {
        loadResources(location, userResources);
    }
}


bool Session::save(QFile & file, QStringList & log) {
    
    log.clear();
    bool written = false;
    if (!atlas->isValid()) {
        log.append("Atlas not valid, refusing to save.");
    }
    else {
        written = writeAtlas(atlas, file, log);
        if (written) {
            fileName = file.fileName();
        }
    }
    
    return written;
}


void Session::selectAtlas() {
    selectMap(QString::null);
    selectRegion(QString::null);
    emit selectedAtlas();
}


void Session::selectMap(QString name) {

    if ((name != QString::null) && !findMap(name)->isValid()) {
        return;
    }
    
    if (name != currentMapName) {
        
        QString oldRegionName = currentRegionName;
        if (name == QString::null) {
            currentRegionName = getRegionOfMap(currentMapName);
        }
        else {
            currentRegionName = getRegionOfMap(name);
        }
    
        currentMapName = name;
        emit selectedRegion(currentRegionName);
        emit selectedMap(currentMapName);
    }
}


void Session::selectRegion(QString name) {
    
    if ((name != QString::null) &&  !findRegion(name)->isValid()) {
        return;
    }
    
    if (name != currentRegionName) {
        currentRegionName = name;
        emit selectedRegion(currentRegionName);
    }
    
    if (!currentMapName.isEmpty()) {
        currentMapName = QString::null;
        emit selectedMap(currentMapName);
    }
}


void Session::setCurrentSession(SessionPointer session) {
    if (!session) {
        throw rpgmapper::model::exception::invalid_session();
    }
    currentSession = session;
}


void loadResources(UNUSED QDir folder, UNUSED ResourceDBPointer db) {
    // TODO
}

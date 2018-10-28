/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


/**
 * The one and only current session.
 */
static QSharedPointer<Session> currentSession;


Session::Session(QObject * parent)
        : QObject(parent) {
    
}


QSharedPointer<rpgmapper::model::Map> & Session::createMap(QString mapName, QString regionName) {

}


QSharedPointer<rpgmapper::model::Region> & Session::createRegion(QString name){

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


QSharedPointer<rpgmapper::model::Region> Session::findRegion(QString name) {
    
    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    return (*iter).second;
}


QSharedPointer<rpgmapper::model::Region> const Session::findRegion(QString name) const {
    
    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    return (*iter).second;
}


std::set<QString> Session::getAllMapNames() const {

}


std::set<QString> Session::getAllRegionNames() const {

}


QSharedPointer<Session> Session::getCurrentSession() {
    return currentSession;
}

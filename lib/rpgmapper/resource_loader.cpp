/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QApplication>
#include <QDateTime>
#include <QStandardPaths>
#include <QStringList>
#include <QTimer>

#include <rpgmapper/resource_loader.hpp>

using namespace rpgmapper::model;


/**
 * Appends a single entry to the log, keeps formatting with timestamps.
 *
 * @param   log         the log to fill.
 * @param   entry       the entry to add
 */
static void appendLog(QStringList & log, QString entry);


/**
 * Grabs a list of system resources to load.
 *
 * @return  the list of files to load from the system.
 */
static QStringList collectSystemResources();


/**
 * Grabs a list of user resources to load.
 *
 * @param   userFolders     the list of user defined folders to search.
 * @return  the list of files to load from the user.
 */
static QStringList collectUserResources(QStringList const & userFolders);


ResourceLoader::ResourceLoader(QObject * parent) : QObject{parent} {
}


void ResourceLoader::load(QStringList & log) {
    
    appendLog(log, "Staring up...");
    
    ResourceLoadingEvent event = {"Collecting system resources...", 0, 0};
    emit loading(event);
    QApplication::processEvents();
    
    auto systemResourcesFiles = collectSystemResources();
    
    event = {"Collecting system resources...", 0, 0};
    emit loading(event);
    QApplication::processEvents();
    auto userResourcesFiles = collectUserResources(userFolders);
    
    QTimer::singleShot(2000, this, &ResourceLoader::done);
}


void appendLog(QStringList & log, QString entry) {
    auto now = QDateTime::currentDateTime();
    log.append(QString{"%1 - %2"}.arg(now.toString(Qt::ISODate)).arg(entry));
}


QStringList collectSystemResources() {
    
    QStringList files;
    
    for (auto const & path : QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)) {
    }

    return files;
}


QStringList collectUserResources(QStringList const & userFolders) {
    
    
    QStringList files;
    
    for (auto const & path : userFolders) {
    }
    return files;
}

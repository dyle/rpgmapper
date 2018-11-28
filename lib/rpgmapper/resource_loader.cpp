/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QStringList>

#include <rpgmapper/resource_loader.hpp>

using namespace rpgmapper::model;


/**
 * Appends a single entry to the log, keeps formatting with timestamps.
 *
 * @param   log         the log to fill.
 * @param   entry       the entry to add
 */
static void appendLog(QStringList & log, QString const & entry);


/**
 * Adds found file to the list of files.
 *
 * If the given fileInfo points to a folder this we add
 * the files found in the folder recursively.
 *
 * @param   files       the list of found files.
 * @param   fileInfo    the current file.
 * @param   log         the log for capturing progress messages
 */
static void collectResources(QStringList & files, QFileInfo const & fileInfo, QStringList & log);


/**
 * Grabs a list of system resources to load.
 *
 * @param   log         the log for capturing progress messages
 * @return  the list of files to load from the system.
 */
static QStringList collectSystemResources(QStringList & log);


/**
 * Grabs a list of user resources to load.
 *
 * @param   userFolders     the list of user defined folders to search.
 * @param   log         the log for capturing progress messages
 * @return  the list of files to load from the user.
 */
static QStringList collectUserResources(QStringList const & userFolders, QStringList & log);


ResourceLoader::ResourceLoader(QObject * parent) : QObject{parent} {
#ifdef SOURCE_PATH
    userFolders.append(QString{SOURCE_PATH} + "/share/rpgmapper");
#endif
}


void ResourceLoader::load(QStringList & log) {
    
    appendLog(log, "Loading Resources...");
    
    ResourceLoadingEvent event = {"Collecting system resources...", 0, 0};
    emit loading(event);
    QApplication::processEvents();
    auto systemResourcesFiles = collectSystemResources(log);
    appendLog(log, QString{"Found %1 system resources."}.arg(systemResourcesFiles.size()));
    
    event = {"Collecting user resources...", 0, 0};
    emit loading(event);
    QApplication::processEvents();
    auto userResourcesFiles = collectUserResources(userFolders, log);
    appendLog(log, QString{"Found %1 user resources."}.arg(userResourcesFiles.size()));
    
    emit done();
}


void appendLog(QStringList & log, QString const & entry) {
    auto now = QDateTime::currentDateTime();
    log.append(QString{"[%1] %2"}.arg(now.toString(Qt::ISODate)).arg(entry));
}


void collectResources(QStringList & files, QFileInfo const & fileInfo, QStringList & log) {
    
    appendLog(log, "Searching: " + fileInfo.absoluteFilePath());
    if (!fileInfo.exists()) {
        return;
    }
    
    if (fileInfo.isDir()) {
        auto directory = QDir{fileInfo.absoluteFilePath()};
        for (auto const & fileInfoInDirectory : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
            collectResources(files, fileInfoInDirectory, log);
        }
    }
    else if (fileInfo.isFile()) {
        files.append(fileInfo.absoluteFilePath());
    }
}


QStringList collectSystemResources(QStringList & log) {
    
    QStringList files;
    QStringList const resourceLocations = {"res", "resource", "resources"};
    
    for (auto const & location : QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)) {
        for (auto const & resourceLocation : resourceLocations) {
            collectResources(files, QFileInfo{location + "/" + resourceLocation}, log);
        }
    }
    return files;
}


QStringList collectUserResources(QStringList const & userFolders, QStringList & log) {
    
    QStringList files;
    QStringList const resourceLocations = {"res", "resource", "resources"};
    
    for (auto const & location : userFolders) {
        for (auto const & resourceLocation : resourceLocations) {
            collectResources(files, QFileInfo{location + "/" + resourceLocation}, log);
        }
    }
    return files;
}

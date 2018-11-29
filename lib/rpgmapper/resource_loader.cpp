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

#include <rpgmapper/resource_db.hpp>
#include <rpgmapper/resource_loader.hpp>
#include <rpgmapper/session.hpp>

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
 * @param   fileCollection               the list of found files.
 * @param   resourceFolder      parent resource folder.
 * @param   fileInfo            the current file.
 * @param   log                 the log for capturing progress messages
 */
static void collectResources(ResourceLoader::FileCollection & fileCollection,
        QString const & resourceFolder,
        QFileInfo const & fileInfo,
        QStringList & log);


/**
 * Grabs a list of system resources to load.
 *
 * @param   fileCollection       the files found
 * @param   log         the log for capturing progress messages
 */
static void collectSystemResources(ResourceLoader::FileCollection & fileCollection, QStringList & log);


/**
 * Grabs a list of user resources to load.
 *
 * @param   files           the files found
 * @param   userFolders     the list of user defined folders to search.
 * @param   log             the log for capturing progress messages
 */
static void collectUserResources(ResourceLoader::FileCollection & files,
        QStringList const & userFolders,
        QStringList & log);


ResourceLoader::ResourceLoader(QObject * parent) : QObject{parent} {
#ifdef SOURCE_PATH
    userFolders.append(QString{SOURCE_PATH} + "/share/rpgmapper");
#endif
}


void ResourceLoader::load(QStringList & log) {
    
    appendLog(log, "Collecting Resources...");
    
    LoadingEvent event = {"Collecting system resources...", 0, 0};
    emit loading(event);
    QApplication::processEvents();
    FileCollection systemResourcesFiles;
    collectSystemResources(systemResourcesFiles, log);
    appendLog(log, QString{"Found %1 system resources."}.arg(systemResourcesFiles.size()));
    
    event = {"Collecting user resources...", 0, 0};
    emit loading(event);
    QApplication::processEvents();
    FileCollection userResourcesFiles;
    collectUserResources(userResourcesFiles, userFolders, log);
    appendLog(log, QString{"Found %1 user resources."}.arg(userResourcesFiles.size()));
    
    appendLog(log, "Loading Resources...");
    loadResources(systemResourcesFiles, Session::getSystemResourceDB(), log);
    loadResources(userResourcesFiles, Session::getUserResourceDB(), log);
    
    emit done();
}


void ResourceLoader::loadResources(FileCollection const & fileCollection, ResourceDBPointer db, QStringList & log) {
    
    int fileNumber = 1;
    for (auto const & fileTuple : fileCollection) {
        
        auto fileName = std::get<1>(fileTuple);
    
        appendLog(log, QString{"Loading: %1..."}.arg(fileName));
        LoadingEvent event = {fileName, fileNumber, static_cast<int>(fileCollection.size())};
        emit loading(event);
        QApplication::processEvents();
        
        QFile file{fileName};
        if (!file.open(QIODevice::ReadOnly)) {
            appendLog(log, QString{"Failed to open: %1"}.arg(fileName));
        }
        else {
    
            auto const & folder = std::get<0>(fileTuple);
            auto resourceName = fileName.right(fileName.size() - folder.size());
            auto byteArray = file.readAll();
            file.close();
            db->addResource(resourceName, byteArray);
        }
        
        fileNumber++;
    }
}


void appendLog(QStringList & log, QString const & entry) {
    auto now = QDateTime::currentDateTime();
    log.append(QString{"[%1] %2"}.arg(now.toString(Qt::ISODate)).arg(entry));
}


void collectResources(ResourceLoader::FileCollection & fileCollection,
        QString const & resourceFolder,
        QFileInfo const & fileInfo,
        QStringList & log) {
    
    appendLog(log, "Searching: " + fileInfo.absoluteFilePath());
    if (!fileInfo.exists()) {
        return;
    }
    
    if (fileInfo.isDir()) {
        auto directory = QDir{fileInfo.absoluteFilePath()};
        for (auto const & fileInfoInDirectory : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
            collectResources(fileCollection, resourceFolder, fileInfoInDirectory, log);
        }
    }
    else if (fileInfo.isFile()) {
        fileCollection.push_back({resourceFolder, fileInfo.absoluteFilePath()});
    }
}


void collectSystemResources(ResourceLoader::FileCollection & fileCollection, QStringList & log) {
    
    QStringList const resourceLocations = {"res", "resource", "resources"};
    
    for (auto const & location : QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)) {
        for (auto const & resourceLocation : resourceLocations) {
            auto folder = location + "/" + resourceLocation;
            collectResources(fileCollection, folder, QFileInfo{location + "/" + resourceLocation}, log);
        }
    }
}


void collectUserResources(ResourceLoader::FileCollection & fileCollection,
        QStringList const & userFolders,
        QStringList & log) {
    
    QStringList const resourceLocations = {"res", "resource", "resources"};
    
    for (auto const & location : userFolders) {
        for (auto const & resourceLocation : resourceLocations) {
            auto folder = location + "/" + resourceLocation;
            collectResources(fileCollection, folder, QFileInfo{folder}, log);
        }
    }
}

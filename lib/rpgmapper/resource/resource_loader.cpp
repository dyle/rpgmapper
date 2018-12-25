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
#include <QMimeDatabase>
#include <QMimeType>
#include <QStandardPaths>
#include <QStringList>

#include <rpgmapper/resource/background.hpp>
#include <rpgmapper/resource/colorpalette.hpp>
#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/resource_loader.hpp>
#include <rpgmapper/resource/resource_type.hpp>
#include <rpgmapper/resource/shape.hpp>
#include <rpgmapper/resource/shape_catalog.hpp>

using namespace rpgmapper::model::resource;


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


ResourcePointer ResourceLoader::createBackground(QString path, QByteArray const & data, QStringList & log) {
    
    ResourcePointer background;
    
    if (Background::isBackground(data)) {
        background = ResourcePointer(new Background{path, data});
    }
    else {
        appendLog(log, QString{"Resource data at %1 is not a background as claimed."}.arg(path));
    }
    
    return background;
}


ResourcePointer ResourceLoader::createColorPalette(QString path, QByteArray const & data, QStringList & log) {
    
    ResourcePointer colorPalette;
    
    if (ColorPalette::isColorPalette(data)) {
        colorPalette = ResourcePointer(new ColorPalette{path, data});
    }
    else {
        appendLog(log, QString{"Resource data at %1 is not a color palette as claimed."}.arg(path));
    }
    
    return colorPalette;
}


ResourcePointer ResourceLoader::createResource(QString path, QByteArray const & data, QStringList & log) {
    
    ResourcePointer resource;
    
    if (data.isEmpty()) {
        appendLog(log, "Resource data is empty. Refusing to create empty resource.");
        return resource;
    }
    
    auto resourceType = suggestResourceTypeByPath(path);
    switch (resourceType) {
        
        case ResourceType::unknown:
            resource = createUnknownResource(path, data);
            break;
            
        case ResourceType::background:
            resource = createBackground(path, data, log);
            break;
    
        case ResourceType::colorpalette:
            resource = createColorPalette(path, data, log);
            break;
            
        case ResourceType::shape:
            
            if (ShapeCatalog::isShapeCatalog(data)) {
                resource = createShapeCatalog(path, data, log);
            }
            else
            if (Shape::isShape(data)) {
                resource = createShape(path, data, log);
            }
            else {
                appendLog(log, QString{"Resource %1 is neither shape catalog nor shape."}.arg(path));
            }
            break;
    }
    
    return resource;
}


ResourcePointer ResourceLoader::createShape(QString path, QByteArray const & data, QStringList & log) {
    
    ResourcePointer shape;
    
    if (Shape::isShape(data)) {
        shape = ResourcePointer(new Shape{path, data});
    }
    else {
        appendLog(log, QString{"Resource data at %1 is not a shape as claimed."}.arg(path));
    }
    
    return shape;
}


ResourcePointer ResourceLoader::createShapeCatalog(QString path, QByteArray const & data, QStringList & log) {
    
    ResourcePointer shapeCatalog;
    
    if (ShapeCatalog::isShapeCatalog(data)) {
        shapeCatalog = ResourcePointer(new ShapeCatalog{path, data});
    }
    else {
        appendLog(log, QString{"Resource data at %1 is not a shape catalog as claimed."}.arg(path));
    }
    
    return shapeCatalog;
}


ResourcePointer ResourceLoader::createUnknownResource(QString path, QByteArray const & data) {
    return ResourcePointer(new Resource{std::move(path), data});
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
    loadResources(systemResourcesFiles, ResourceDB::getSystemResources(), log);
    loadResources(userResourcesFiles, ResourceDB::getUserResources(), log);
    
    success = true;
    emit done();
}


ResourcePointer ResourceLoader::load(QString filePath, QString fileRoot, QStringList & log) {
    
    ResourcePointer resource;
    
    QFile file{filePath};
    if (!file.open(QIODevice::ReadOnly)) {
        appendLog(log, QString{"Failed to open: %1"}.arg(filePath));
    }
    else {
        
        auto byteArray = file.readAll();
        file.close();
        auto resourcePath = filePath.right(filePath.size() - fileRoot.size());
        resource = createResource(resourcePath, byteArray, log);
    }
    
    return resource;
}


void ResourceLoader::loadResources(FileCollection const & fileCollection,
        ResourceCollectionPointer collection,
        QStringList & log) {
    
    int fileNumber = 1;
    for (auto const & fileTuple : fileCollection) {
        
        auto const & fileName = std::get<1>(fileTuple);
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
            auto resourcePath = fileName.right(fileName.size() - folder.size());
            auto data = file.readAll();
            file.close();
            
            auto resource = createResource(resourcePath, data, log);
            if (resource) {
                collection->addResource(resource);
            }
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

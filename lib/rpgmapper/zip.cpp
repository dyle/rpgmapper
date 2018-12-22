/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

#include <QDateTime>
#include <QJsonDocument>

#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/resource_loader.hpp>
#include <rpgmapper/atlas.hpp>

#include "content.hpp"
#include "zip.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::model::resource;

// TODO: remove when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   ifndef UNUSED
#       define UNUSED   __attribute__((unused))
#   endif
#else
#   define UNUSED
#endif


/**
 * Adds all atlas local resources to the content.
 *
 * @param   content     the content to collect the local resources.
 * @param   log         protocol of actions.
 */
static void addLocalResourcesToContent(Content & content, QStringList & log);


/**
 * Appends some content to an opened zip.
 *
 * @param   content     the content to add.
 * @param   zip         the zip structure to fill.
 * @param   log         protocol of actions.
 * @return  true, if successfully added
 */
static bool appendContentToZip(Content const & content, QuaZip & zip, QStringList & log);


/**
 * Appends a named BLOB to a zip.
 *
 * @param   name        the name of the BLOB to add.
 * @param   blob        the BLOB.
 * @param   zip         the zip structure to fill.
 * @param   log         the protocol of actions.
 * @return  true, if successfully added
 */
static bool appendFileToZip(QString const & name, QByteArray const & blob, QuaZip & zip, QStringList & log);


/**
 * Closes a zipfile.
 *
 * @param   zip     Zip file functions class.
 * @param   log     Huamn Readable logs (appended).
 */
static void closeZip(QuaZip & zip, QStringList & log);


/**
 * Creates an atlas from a loaded content.
 *
 * @param   atlas           the atlas to be created.
 * @param   content         the loaded content.
 * @param   log             the protocol.
 * @return  true, for a successful loaded atlas.
 */
static bool createAtlasFromContent(AtlasPointer & atlas, Content const & content, QStringList & log);


/**
 * Creates an atlas from a loaded content.
 *
 * @param   atlas           the atlas to be created.
 * @param   json            the atlas.json loaded.
 * @param   log             the protocol.
 * @return  true, for a successful loaded atlas.
 */
static bool createAtlasFromJSON(AtlasPointer & atlas, QJsonDocument const & json, QStringList & log);


/**
 * Creates some meta information to be added to the atlas file.
 *
 * @return  JSON document holding the meta information.
 */
static QJsonDocument createMetaInformation();


/**
 * Extracts the content (a set of named blobs) from the zip.
 *
 * @param   zip         the zip to extract from.
 * @param   content     the content to fill.
 * @param   log         protocol of actions.
 * @return  true, for success.
 */
static bool extractContentFromZip(QuaZip & zip, Content & content, QStringList & log);

/**
 * Loads the local resources from the content.
 *
 * @param   content     the content loaded.
 * @param   log         protocol of actions
 */
static void loadLocalResources(Content const & content, QStringList & log);

/**
 * Opens a zip file for reading.
 *
 * @param   zip     Zip file functions class.
 * @param   file    the file to open.
 * @param   log     Huamn Readable logs (appended).
 * @return  true, for successful close.
 */
static bool openZipForReading(QuaZip & zip, QFile & file, QStringList & log);


/**
 * Opens a zip file for writing.
 *
 * @param   zip     Zip file functions class.
 * @param   file    the file to open.
 * @param   log     Huamn Readable logs (appended).
 * @return  true, for successful close.
 */
static bool openZipForWriting(QuaZip & zip, QFile & file, QStringList & log);


void addLocalResourcesToContent(Content & content, QStringList & log) {

    log.append("Adding local resources.");
    auto localResources = ResourceDB::getLocalResources();
    for (auto const & pair : localResources->getResources()) {
        auto resource = pair.second;
        log.append(QString{"Adding: "} + resource->getName());
        content[resource->getName()] = resource->getData();
    }
}


bool appendContentToZip(Content const & content, QuaZip & zip, QStringList & log) {
    
    bool res = true;
    for (auto const & pair : content) {
        res = appendFileToZip(pair.first, pair.second, zip, log);
        if (!res) {
            break;
        }
    }
    
    return res;
}


bool appendFileToZip(QString const & name, QByteArray const & blob, QuaZip & zip, QStringList & log) {
    
    QuaZipFile zf(&zip);
    QuaZipNewInfo zfi(name);
    constexpr QFile::Permissions permissions = QFile::ReadOwner |
                                               QFile::WriteOwner |
                                               QFile::ReadGroup |
                                               QFile::WriteGroup |
                                               QFile::ReadOther;
    zfi.setPermissions(permissions);

    bool res = zf.open(QIODevice::WriteOnly, zfi);
    if (!res) {
        log.append(QString{"Failed to write sub file '"} + zf.getActualFileName() + "'.");
    }
    else {
        zf.write(blob.data(), blob.size());
        log.append(QString{"Written sub file '"} + zf.getActualFileName() + "'.");
    }
    
    return res;
}


void closeZip(QuaZip & zip, QStringList & log) {
    zip.close();
    log.append("Closed.");
}


bool createAtlasFromContent(AtlasPointer & atlas, Content const & content, QStringList & log) {
    
    bool res;
    
    if (content.find("atlas.json") == content.end()) {
        res = false;
        log.append("Atlas json not found in file.");
    }
    else {
        res = createAtlasFromJSON(atlas, QJsonDocument::fromJson(content.at("atlas.json")), log);
    }
    
    return res;
}


bool createAtlasFromJSON(AtlasPointer & atlas, QJsonDocument const & json, QStringList & log) {
    
    bool res = true;
    
    if (json.isNull()) {
        res = false;
        log.append("Contained atlas not a JSON. Corrupted? Unable to load.");
    }
    else
    if (!json.isObject()) {
        res = false;
        log.append("Contained atlas not an JSON object. Corrupted? Unable to load.");
    }
    else {
        
        atlas->applyJSON(json.object());
        if (atlas->isValid()) {
            log.append("Loaded atlas.");
        }
    }
    
    return res;
}


static QJsonDocument createMetaInformation() {
    
    QJsonObject json;
    json["version"] = VERSION;
    
    QString user = qgetenv("USER");
    if (user.isEmpty()) {
        user = qgetenv("USERNAME");
    }
    json["user"] = user;
    
    auto currentTime = QDateTime::currentDateTime();
    json["datetime"] = currentTime.toString(Qt::ISODate);
    
    QJsonDocument jsonDocument;
    jsonDocument.setObject(json);
    return jsonDocument;
}


bool extractContentFromZip(QuaZip & zip, Content & content, QStringList & log) {
    
    QuaZipFileInfo zfi;
    bool res = zip.getCurrentFileInfo(&zfi);
    if (!res) {
        log.append("Failed to get current sub file info.");
    }
    else {
        
        QuaZipFile zf(&zip);
        res = zf.open(QIODevice::ReadOnly);
        if (!res) {
            log.append("Failed to open current sub file.");
        }
        else {
            
            QByteArray blob;
            blob.resize(zfi.uncompressedSize);
            zf.read(blob.data(), zfi.uncompressedSize);
            
            auto filenameInZip = zf.getActualFileName();
            content.insert(std::make_pair(filenameInZip, blob));
            log.append("Found: " + filenameInZip);
        }
    }
    
    return res;
}


void loadLocalResources(Content const & content, QStringList & log) {
    
    log.append("Loading local resources.");
    for (auto const & pair : content) {
        
        QString const & path = pair.first;
        QByteArray const & data = pair.second;
        
        auto resource = ResourceLoader::createResource(path, data, log);
        if (resource) {
            ResourceDB::getLocalResources()->addResource(resource);
            log.append(QString{"Added : "} + path);
        }
    }
}


bool openZipForReading(QuaZip & zip, QFile & file, QStringList & log) {
    
    bool res = true;
    
    zip.setZipName(file.fileName());
    zip.setFileNameCodec("UTF-8");
    if (!zip.open(QuaZip::mdUnzip, nullptr)) {
        res = false;
        log.append(QString{"Failed to open file '"} + file.fileName() + "' for decompression.");
    }
    else {
        log.append(QString{"Opened file '"} + file.fileName() + "' for decompression.");
    }
    
    return res;
}


bool openZipForWriting(QuaZip & zip, QFile & file, QStringList & log) {
    
    bool res = true;
    
    zip.setZipName(file.fileName());
    zip.setFileNameCodec("UTF-8");
    if (!zip.open(QuaZip::mdCreate, nullptr)) {
        res = false;
        log.append(QString{"Failed to create file '"} + file.fileName() + "' for compression.");
    }
    else {
        log.append(QString{"Created file '"} + file.fileName() + "' for compression.");
        
    }
    
    return res;
}


bool rpgmapper::model::readAtlas(AtlasPointer & atlas, QFile & file, QStringList & log) {
    
    QuaZip zip;
    bool res = openZipForReading(zip, file, log);
    if (res) {
    
        Content content;
        for (auto filePresent = zip.goToFirstFile(); filePresent && res; filePresent = zip.goToNextFile()) {
            res = extractContentFromZip(zip, content, log);
        }
    
        if (res) {
            res = createAtlasFromContent(atlas, content, log);
        }
        
        loadLocalResources(content, log);
        
        closeZip(zip, log);
    }
    
    return res;
}


bool rpgmapper::model::writeAtlas(AtlasPointer const & atlas, QFile & file, QStringList & log) {
    
    QuaZip zip;
    
    bool res = openZipForWriting(zip, file, log);
    if (res) {
    
        Content content;
        auto metaJson = createMetaInformation();
        content["meta.json"] = metaJson.toJson(QJsonDocument::Compact);
        log.append("Added: meta.json.");
        
        QJsonDocument json;
        json.setObject(atlas->getJSON());
        content["atlas.json"] = json.toJson(QJsonDocument::Compact);
        log.append("Added: atlas.json.");
        
        addLocalResourcesToContent(content, log);
        
        res = appendContentToZip(content, zip, log);
        closeZip(zip, log);
    }
    
    return res;
}

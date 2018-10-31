/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

#include <QJsonDocument>

#include <rpgmapper/io/content.hpp>
#include "zip.hpp"

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {
namespace io {


/**
 * Appends some content to an opened zip.
 *
 * @param   content     the content to add.
 * @param   zip         the zip structure to fill.
 * @param   log         protocol of actions.
 * @return  true, if successfully added
 */
static bool appendContent(Content const & content, QuaZip & zip, QStringList & log);


/**
 * Appends a named BLOB to a zip.
 *
 * @param   name        the name of the BLOB to add.
 * @param   blob        the BLOB.
 * @param   zip         the zip structure to fill.
 * @param   log         the protocol of actions.
 * @return  true, if successfully added
 */
static bool appendFile(QString const & name, QByteArray const & blob, QuaZip & zip, QStringList & log);


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
static bool createAtlas(QSharedPointer<rpgmapper::model::Atlas> & atlas, Content const & content, QStringList & log);


/**
 * Creates an atlas from a loaded content.
 *
 * @param   atlas           the atlas to be created.
 * @param   content         the loaded content.
 * @param   json            the atlas.json loaded.
 * @param   log             the protocol.
 * @return  true, for a successful loaded atlas.
 */
static bool createAtlasFromJSON(QSharedPointer<rpgmapper::model::Atlas> & atlas,
        Content const & content,
        QJsonDocument const & json,
        QStringList & log);


/**
 * Extracts the content (a set of named blobs) from the zip.
 *
 * @param   zip         the zip to extract from.
 * @param   content     the content to fill.
 * @param   log         protocol of actions.
 * @return  true, for success.
 */
static bool extractContent(QuaZip & zip, Content & content, QStringList & log);


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


}
}
}


bool rpgmapper::model::io::appendContent(Content const & content, QuaZip & zip, QStringList & log) {
    
    bool res = true;
    for (auto const & pair : content) {
        res = appendFile(pair.first, pair.second, zip, log);
        if (!res) {
            break;
        }
    }
    
    return res;
}


bool rpgmapper::model::io::appendFile(QString const & name, QByteArray const & blob, QuaZip & zip, QStringList & log) {
    
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


void rpgmapper::model::io::closeZip(QuaZip & zip, QStringList & log) {
    zip.close();
    log.append("Closed.");
}


bool rpgmapper::model::io::createAtlas(QSharedPointer<rpgmapper::model::Atlas> & atlas,
        Content const & content,
        QStringList & log) {
    
    bool res = true;
    
    if (content.find("atlas.json") == content.end()) {
        res = false;
        log.append("Atlas json not found in file.");
    }
    else {
        res = createAtlasFromJSON(atlas, content, QJsonDocument::fromJson(content.at("atlas.json")), log);
    }
    
    return res;
}


bool rpgmapper::model::io::createAtlasFromJSON(QSharedPointer<rpgmapper::model::Atlas> & atlas,
        Content const & content,
        QJsonDocument const & json,
        QStringList & log) {
    
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
        
        atlas = QSharedPointer<rpgmapper::model::Atlas>{new Atlas};
        atlas->applyJSON(json.object());
        if (atlas->isValid()) {
            log.append("Loaded atlas.");
        }
    }
    
    return res;
}


bool rpgmapper::model::io::extractContent(QuaZip & zip, Content & content, QStringList & log) {
    
    QuaZipFileInfo zfi;
    bool res = zip.getCurrentFileInfo(&zfi);
    if (!res) {
        log.append("Failed to get current sub file info.");
    }
    else {
        
        QuaZipFile zf(&zip);
        res = zf.open(QIODevice::ReadOnly);
        if (res) {
            log.append("Failed to open current sub file.");
        }
        else {
            
            QByteArray blob;
            blob.resize(zfi.uncompressedSize);
            zf.read(blob.data(), zfi.uncompressedSize);
        
            content.insert(std::make_pair(zf.getActualFileName(), blob));
        }
    }
    
    return res;
}


bool rpgmapper::model::io::openZipForReading(QuaZip & zip, QFile & file, QStringList & log) {
    
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


bool rpgmapper::model::io::openZipForWriting(QuaZip & zip, QFile & file, QStringList & log) {
    
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



bool rpgmapper::model::io::readAtlas(QSharedPointer<rpgmapper::model::Atlas> & atlas, QFile & file, QStringList & log) {
    
    QuaZip zip;
    bool res = openZipForReading(zip, file, log);
    if (res) {
    
        Content content;
        for (auto filePresent = zip.goToFirstFile(); filePresent && res; filePresent = zip.goToNextFile()) {
            res = extractContent(zip, content, log);
        }
    
        if (res) {
            res = createAtlas(atlas, content, log);
        }
        
        closeZip(zip, log);
    }
    
    return res;
}


bool rpgmapper::model::io::writeAtlas(QSharedPointer<rpgmapper::model::Atlas> const & atlas, QFile & file, QStringList & log) {
    
    QuaZip zip;
    bool res = openZipForWriting(zip, file, log);
    
    if (res) {
    
        Content content;
        atlas->collectIOContent(content);
        res = appendContent(content, zip, log);
        if (res) {
            atlas->resetChanged();
        }
    
        closeZip(zip, log);
    }
    
    return res;
}

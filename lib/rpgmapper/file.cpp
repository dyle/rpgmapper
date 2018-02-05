/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */



#include <QJsonDocument>

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>
#include <rpgmapper/types.hpp>


using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Get the file name to save.
 * If the given filename is set, the we remember this one in
 * future calls. If the given filename is empty, this method
 * places the once remembered filename in the given parameter.
 *
 * @param   sFileName   will be the new filename to save
 * @return  true, if we have a valid filename
 */
bool File::acquireFileName(QString & sFileName) {

    if (!sFileName.isEmpty()) {
        m_sFileName = sFileName;
    }
    else {
        sFileName = m_sFileName;
    }

    return !sFileName.isEmpty();
}


/**
 * Gather the internal atlas file.
 */
void File::collectAtlasFile() {
    QJsonObject cJSONAtlas;
    Controller::instance().atlas()->save(cJSONAtlas);
    QJsonDocument cJSONDoc(cJSONAtlas);
    m_cFiles["atlas.json"] = cJSONDoc.toJson(QJsonDocument::Compact);
}


/**
 * Extract the atlas file and apply it to the controller atlas instance.
 */
void File::extractAtlasFile() {
    auto cJSONDoc = QJsonDocument::fromJson(m_cFiles["atlas.json"]);
    Controller::instance().atlas()->load(cJSONDoc.object());
}


/**
 * Load a file, reset data.
 *
 * @param   sFileName       name of the file to load
 * @param   cLog            log of operations done
 * @return  true, for success
 */
bool File::load(QString & sFileName, QStringList & cLog) {

    cLog.clear();
    if (!acquireFileName(sFileName)) {
        cLog.append("File setName is empty. Don't know what to load.");
        return false;
    }

    QuaZip cQuaZip;
    cQuaZip.setZipName(sFileName);
    if (!cQuaZip.open(QuaZip::mdUnzip)) {
        cLog.append("Failed to open file '" + sFileName + "' to uncompress.");
        return false;
    }
    cLog.append("Opened file '" + sFileName + "' to uncompress.");

    for (auto bFilePresent = cQuaZip.goToFirstFile(); bFilePresent; bFilePresent = cQuaZip.goToNextFile()) {

        QuaZipFileInfo zfi;
        if (!cQuaZip.getCurrentFileInfo(&zfi)) {
            cLog.append("Failed to get current sub file info.");
            return false;
        }

        QuaZipFile zf(&cQuaZip);
        if (!zf.open(QIODevice::ReadOnly)) {
            cLog.append("Failed to open current sub file.");
            return false;
        }

        QByteArray cData;
        cData.resize(zfi.uncompressedSize);
        zf.read(cData.data(), zfi.uncompressedSize);

        m_cFiles.insert(std::make_pair(zf.getActualFileName(), cData));
    }

    cQuaZip.close();
    cLog.append("File '" + sFileName + "' loaded.");

    if (m_cFiles.find("atlas.json") == m_cFiles.end()) {
        cLog.append("Atlas not found in file. Is this a regular atlas file for RPGMapper?");
        return false;
    }

    auto cJSONDoc = QJsonDocument::fromJson(m_cFiles["atlas.json"]);
    if (cJSONDoc.isNull()) {
        cLog.append("Contained atlas not a JSON. Corrupted? Unable to load.");
        return false;
    }
    if (!cJSONDoc.isObject()) {
        cLog.append("Contained atlas not an JSON object. Corrupted? Unable to load.");
        return false;
    }

    return true;
}


/**
 * Save all internal files into a single file.
 *
 * @param   sFileName       name of the file to save
 * @param   cLog            log of operations done
 * @return  true, for success
 */
bool File:: save(QString & sFileName, QStringList & cLog) {

    cLog.clear();
    if (!acquireFileName(sFileName)) {
        cLog.append("File setName is empty. Don't know what to load.");
        return false;
    }

    collectAtlasFile();

    QuaZip cQuaZip;
    cQuaZip.setZipName(sFileName);
    cQuaZip.setFileNameCodec("UTF-8");
    if (!cQuaZip.open(QuaZip::mdCreate, nullptr)) {
        cLog.append("Failed to create file '" + sFileName + "' for compression.");
        return false;
    }
    cLog.append("Created file '" + sFileName + "' for compression.");

    for (auto const & cEntry: m_cFiles) {

        QuaZipFile zf(&cQuaZip);
        QuaZipNewInfo zfi(cEntry.first);

        if (!zf.open(QIODevice::WriteOnly, zfi)) {
            cLog.append("Filed to write sub file '" + zf.getActualFileName() + "'.");
            return false;
        }

        zf.write(cEntry.second.data(), cEntry.second.size());
    }

    cQuaZip.close();
    cLog.append("File '" + sFileName + "' saved.");

    return true;
}

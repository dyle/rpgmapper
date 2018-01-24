/*
 * file.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// ------------------------------------------------------------
// incs

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
 * Collect all necessary internal files.
 */
void File::collectInternalFiles() {
    m_cFiles.clear();
    collectAtlasFile();
}


/**
 * Load a file, reset data.
 *
 * @param   sFileName       name of the file to load
 * @param   cLog            log of operations done
 * @return  true, for success
 */
bool File::load(QString sFileName, QStringList & cLog) {

    cLog.clear();
    if (!acquireFileName(sFileName)) {
        cLog.append("File name is empty. Don't know what to load.");
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

    Controller::instance().atlas()->modified(false);

    return true;
}


/**
 * Save all internal files into a single file.
 *
 * @param   sFileName       name of the file to save
 * @param   cLog            log of operations done
 * @return  true, for success
 */
bool File:: save(QString sFileName, QStringList & cLog) {

    cLog.clear();
    if (!acquireFileName(sFileName)) {
        cLog.append("File name is empty. Don't know what to load.");
        return false;
    }

    collectInternalFiles();

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

    Controller::instance().atlas()->modified(false);

    return true;
}

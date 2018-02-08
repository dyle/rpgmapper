/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

#include <rpgmapper/atlas_io.hpp>


using namespace rpgmapper::model;

using Content = std::map<QString, QByteArray>;

IOResult appendContent(Content const & content, QuaZip & zip);

IOResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip);

ReaderResult createAtlas(Content const & content);

IOResult extractContent(QuaZip & zip, Content & content);

IOResult closeZip(QuaZip & zip);

Content collectContent(Atlas const & atlas);

IOResult openZip(QuaZip & zip, QFile & file);


ReaderResult AtlasIO::read(QFile & file) const {

    ReaderResult result;

    QuaZip zip;
    result << openZip(zip, file);
    if (!result.hasSuccess()) {
        return result;
    }

    Content content;
    for (auto filePresent = zip.goToFirstFile(); filePresent; filePresent = zip.goToNextFile()) {
        result << extractContent(zip, content);
        if (!result.hasSuccess()) {
            break;
        }
    }

    result << createAtlas(content);
    result << closeZip(zip);

    return result;
}


IOResult AtlasIO::write(Atlas & atlas, QFile & file) const {

    IOResult result;

    if (!atlas.isValid()) {
        result << false;
        result << "Atlas not valid, refusing to save.";
        return result;
    }

    auto content = collectContent(atlas);

    QuaZip zip;
    result << openZip(zip, file);
    if (!result.hasSuccess()) {
        return result;
    }

    result << appendContent(content, zip);
    if (!result.hasSuccess()) {
        return result;
    }

    result << closeZip(zip);

    return result;
}


IOResult appendContent(Content const & content, QuaZip & zip) {
    IOResult result;
    for (auto const & pair : content) {
        result << appendFile(pair.first, pair.second, zip);
        if (!result.hasSuccess()) {
            return result;
        }
    }
    result << true;
    return result;
}


IOResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip) {

    IOResult result;
    QuaZipFile zf(&zip);
    QuaZipNewInfo zfi(name);
    constexpr QFile::Permissions permissions = QFile::ReadOwner |
                                               QFile::WriteOwner |
                                               QFile::ReadGroup |
                                               QFile::WriteGroup |
                                               QFile::ReadOther;
    zfi.setPermissions(permissions);

    if (!zf.open(QIODevice::WriteOnly, zfi)) {
        result << false;
        result << "Failed to write sub file '" + zf.getActualFileName() + "'.";
        return result;
    }

    zf.write(blob.data(), blob.size());
    result << true;
    result << "Written sub file '" + zf.getActualFileName() + "'.";
    return result;
}


IOResult closeZip(QuaZip & zip) {
    zip.close();
    return IOResult{true, {"Closed."}};
}


Content collectContent(Atlas const & atlas) {
    Content content;
    content["atlas.json"] = QJsonDocument{atlas.getJsonObject()}.toJson(QJsonDocument::Compact);
    return content;
}

ReaderResult createAtlas(Content const & content) {

    ReaderResult result;

    if (content.find("atlas.json") == content.end()) {
        result << false;
        result << "Atlas Json not found in file.";
        return result;

    }

    AtlasPointer atlas{new Atlas};


    /*
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
     */



    return result;
}

IOResult extractContent(QuaZip & zip, Content & content) {

    IOResult result;

    QuaZipFileInfo zfi;
    if (!zip.getCurrentFileInfo(&zfi)) {
        result << false;
        result << "Failed to get current sub file info.";
        return result;
    }

    QuaZipFile zf(&zip);
    if (!zf.open(QIODevice::ReadOnly)) {
        result << false;
        result << "Failed to open current sub file.";
        return result;
    }

    QByteArray blob;
    blob.resize(zfi.uncompressedSize);
    zf.read(blob.data(), zfi.uncompressedSize);

    content.insert(std::make_pair(zf.getActualFileName(), blob));

    result << true;
    return result;
}


IOResult openZip(QuaZip & zip, QFile & file) {

    IOResult result;

    zip.setZipName(file.fileName());
    zip.setFileNameCodec("UTF-8");
    if (!zip.open(QuaZip::mdCreate, nullptr)) {
        result << false;
        result << "Failed to create file '" + file.fileName() + "' for compression.";
        return result;
    }

    result << true;
    result << "Created file '" + file.fileName() + "' for compression.";
    return result;
}

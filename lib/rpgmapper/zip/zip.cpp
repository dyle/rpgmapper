/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "zip.hpp"

using namespace rpgmapper::model;


using Content = std::map<QString, QByteArray>;

IOResult appendContent(Content const & content, QuaZip & zip);

IOResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip);

Content collectContent(AtlasPointer const & atlas);

ReaderResult createAtlas(Content const & content);

IOResult extractContent(QuaZip & zip, Content & content);


IOResult rpgmapper::model::closeZip(QuaZip & zip) {
    zip.close();
    return IOResult{true, {"Closed."}};
}


IOResult rpgmapper::model::openZipForReading(QuaZip & zip, QFile & file) {

    IOResult result;

    zip.setZipName(file.fileName());
    zip.setFileNameCodec("UTF-8");
    if (!zip.open(QuaZip::mdUnzip, nullptr)) {
        result << false;
        result << "Failed to open file '" + file.fileName() + "' for decompression.";
        return result;
    }

    result << true;
    result << "Opened file '" + file.fileName() + "' for decompression.";
    return result;
}


IOResult rpgmapper::model::openZipForWriting(QuaZip & zip, QFile & file) {

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


ReaderResult rpgmapper::model::readAtlas(QuaZip &zip) {
    ReaderResult result;
    Content content;
    for (auto filePresent = zip.goToFirstFile(); filePresent; filePresent = zip.goToNextFile()) {
        result << extractContent(zip, content);
        if (!result.hasSuccess()) {
            break;
        }
    }

    result << createAtlas(content);
    return result;
}


IOResult rpgmapper::model::writeAtlas(QuaZip &zip, AtlasPointer & atlas) {

    IOResult result;

    auto content = collectContent(atlas);
    result << appendContent(content, zip);
    if (!result.hasSuccess()) {
        return result;
    }

    atlas->resetChanged();
    result << true;
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


Content collectContent(AtlasPointer const & atlas) {
    Content content;
    content["atlas.json"] = QJsonDocument{atlas->getJsonObject()}.toJson(QJsonDocument::Compact);
    return content;
}


ReaderResult createAtlas(Content const & content) {

    ReaderResult result;

    if (content.find("atlas.json") == content.end()) {
        result << false;
        result << "Atlas json not found in file.";
        return result;
    }

    auto jsonDocument = QJsonDocument::fromJson(content.at("atlas.json"));
    if (jsonDocument.isNull()) {
        result << false;
        result << "Contained atlas not a JSON. Corrupted? Unable to load.";
        return result;
    }
    if (!jsonDocument.isObject()) {
        result << false;
        result << "Contained atlas not an JSON object. Corrupted? Unable to load.";
        return result;
    }

    AtlasPointer atlas{new Atlas};
    atlas->applyJsonObject(jsonDocument.object());
    if (!atlas->isValid()) {
        result.setAtlas(atlas);
        result << "Loaded atlas.";
    }

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

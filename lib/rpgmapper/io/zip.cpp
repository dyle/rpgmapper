/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/io/content.hpp>
#include "zip.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::model::io;


WriterResult appendContent(Content const & content, QuaZip & zip);

WriterResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip);

Content collectContent(AtlasPointer const & atlas);

ReaderResult createAtlas(Content const & content);

WriterResult extractContent(QuaZip & zip, Content & content);


WriterResult rpgmapper::model::io::closeZip(QuaZip & zip) {
    zip.close();
    return WriterResult{true, {"Closed."}};
}


WriterResult rpgmapper::model::io::openZipForReading(QuaZip & zip, QFile & file) {

    WriterResult result;

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


WriterResult rpgmapper::model::io::openZipForWriting(QuaZip & zip, QFile & file) {

    WriterResult result;

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


ReaderResult rpgmapper::model::io::readAtlas(QuaZip &zip) {

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


WriterResult rpgmapper::model::io::writeAtlas(QuaZip &zip, AtlasPointer & atlas) {

    WriterResult result;

    auto content = collectContent(atlas);
    result << appendContent(content, zip);
    if (!result.hasSuccess()) {
        return result;
    }

    atlas->resetChanged();
    result << true;
    return result;
}


WriterResult appendContent(Content const & content, QuaZip & zip) {

    WriterResult result;

    for (auto const & pair : content) {
        result << appendFile(pair.first, pair.second, zip);
        if (!result.hasSuccess()) {
            return result;
        }
    }

    result << true;
    return result;
}


WriterResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip) {

    WriterResult result;
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
    atlas->collectIOContent(content);
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
    if (atlas->isValid()) {
        atlas->resetChanged();
        result.setAtlas(atlas);
        result << true;
        result << "Loaded atlas.";
    }

    return result;
}


WriterResult extractContent(QuaZip & zip, Content & content) {

    WriterResult result;

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

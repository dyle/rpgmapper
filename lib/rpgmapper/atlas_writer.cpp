/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

#include <rpgmapper/atlas_writer.hpp>


using namespace rpgmapper::model;

using Content = std::map<QString, QByteArray>;

OperationResult appendContent(Content const & content, QuaZip & zip);

OperationResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip);

OperationResult closeZip(QuaZip & zip);

Content collectContent(Atlas const & atlas);

OperationResult openZip(QuaZip & zip, QFile & file);


OperationResult AtlasWriter::write(Atlas & atlas, QFile & file) const {

    OperationResult result;

    if (!atlas.isValid()) {
        result.success = false;
        result.log << "Atlas not valid, refusing to save.";
        return result;
    }

    auto content = collectContent(atlas);

    QuaZip zip;
    result << openZip(zip, file);
    if (!result.success) {
        return result;
    }

    result << appendContent(content, zip);
    if (!result.success) {
        return result;
    }

    result << closeZip(zip);

    return result;
}


OperationResult appendContent(Content const & content, QuaZip & zip) {
    OperationResult result;
    for (auto const & pair : content) {
        result << appendFile(pair.first, pair.second, zip);
        if (!result.success) {
            return result;
        }
    }
    result.success = true;
    return result;
}


OperationResult appendFile(QString const & name, QByteArray const & blob, QuaZip & zip) {

    OperationResult result;
    QuaZipFile zf(&zip);
    QuaZipNewInfo zfi(name);
    constexpr QFile::Permissions permissions = QFile::ReadOwner |
                                               QFile::WriteOwner |
                                               QFile::ReadGroup |
                                               QFile::WriteGroup |
                                               QFile::ReadOther;
    zfi.setPermissions(permissions);

    if (!zf.open(QIODevice::WriteOnly, zfi)) {
        result.success = false;
        result.log << "Failed to write sub file '" + zf.getActualFileName() + "'.";
        return result;
    }

    zf.write(blob.data(), blob.size());
    result.success = true;
    result.log << "Written sub file '" + zf.getActualFileName() + "'.";
    return result;
}


OperationResult closeZip(QuaZip & zip) {
    zip.close();
    return OperationResult{true, {"Closed."}};
}


Content collectContent(Atlas const & atlas) {
    Content content;
    content["atlas.json"] = QJsonDocument{atlas.getJsonObject()}.toJson(QJsonDocument::Compact);
    return content;
}


OperationResult openZip(QuaZip & zip, QFile & file) {

    OperationResult result;

    zip.setZipName(file.fileName());
    zip.setFileNameCodec("UTF-8");
    if (!zip.open(QuaZip::mdCreate, nullptr)) {
        result.success = false;
        result.log << "Failed to create file '" + file.fileName() + "' for compression.";
        return result;
    }

    result.success = true;
    result.log << "Created file '" + file.fileName() + "' for compression.";
    return result;
}

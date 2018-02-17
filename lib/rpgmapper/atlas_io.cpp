/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <quazip/quazip.h>

#include <rpgmapper/atlas_io.hpp>
#include "zip/zip.hpp"

using namespace rpgmapper::model;


ReaderResult AtlasIO::read(QFile & file) const {

    ReaderResult result;

    QuaZip zip;
    result << openZipForReading(zip, file);
    if (!result.hasSuccess()) {
        return result;
    }

    result << readAtlas(zip);
    closeZip(zip);

    result.getAtlas()->setFileName(file.fileName());

    return result;
}


WriterResult AtlasIO::write(AtlasPointer & atlas, QFile & file) const {

    WriterResult result;

    if (!atlas->isValid()) {
        result << false;
        result << "Atlas not valid, refusing to save.";
        return result;
    }

    QuaZip zip;
    result << openZipForWriting(zip, file);
    if (!result.hasSuccess()) {
        return result;
    }

    result << writeAtlas(zip, atlas);
    closeZip(zip);

    atlas->setFileName(file.fileName());

    return result;
}

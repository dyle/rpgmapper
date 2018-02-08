/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

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

    return result;
}


IOResult AtlasIO::write(AtlasPointer & atlas, QFile & file) const {

    IOResult result;

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

    return result;
}

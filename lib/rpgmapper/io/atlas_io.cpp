/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <quazip/quazip.h>

#include <rpgmapper/io/atlas_io.hpp>
#include "zip.hpp"

using namespace rpgmapper::model::io;


ReaderResult AtlasIO::read(QFile & file) const {
    
    auto atlas = AtlasPointer{new InvalidAtlas};
    QStringList log;
    
    bool read = readAtlas(atlas, file, log);
    if (read) {
        atlas->setFileName(file.fileName());
    }
    
    return ReaderResult{atlas, read, log};
}


WriterResult AtlasIO::write(AtlasPointer & atlas, QFile & file) const {
    
    bool written = true;
    QStringList log;
    if (!atlas->isValid()) {
        written = false;
        log.append("Atlas not valid, refusing to save.");
    }
    else {
        written = writeAtlas(atlas, file, log);
        if (written) {
            atlas->setFileName(file.fileName());
        }
    }

    return WriterResult{written, log};
}

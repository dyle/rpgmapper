/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ZIP_ZIP_HPP
#define RPGMAPPER_MODEL_ZIP_ZIP_HPP

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

#include <rpgmapper/atlas_io.hpp>


using namespace rpgmapper::model;

namespace rpgmapper {
namespace model {


WriterResult closeZip(QuaZip & zip);

WriterResult openZipForReading(QuaZip & zip, QFile & file);

WriterResult openZipForWriting(QuaZip & zip, QFile & file);

ReaderResult readAtlas(QuaZip & zip);

WriterResult writeAtlas(QuaZip & zip, AtlasPointer & atlas);


}
}


#endif

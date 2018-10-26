/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_ZIP_ZIP_HPP
#define RPGMAPPER_MODEL_ZIP_ZIP_HPP

#include <rpgmapper/io/atlas_io.hpp>


namespace rpgmapper {
namespace model {
namespace io {


/**
 * Read an atlas from a file.
 *
 * @param   atlas   The atlas read.
 * @param   file    the file to read.
 * @param   log     Huamn Readable logs (appended).
 * @return  true, for successful read.
 */
bool readAtlas(AtlasPointer & atlas, QFile & file, QStringList & log);


/**
 * Writes an atlas to a file.
 *
 * @param   atlas   The atlas to write.
 * @param   file    the file to write.
 * @param   log     Huamn Readable logs (appended).
 * @return  true, for successful write.
 */
bool writeAtlas(AtlasPointer const & atlas, QFile & file, QStringList & log);


}
}
}


#endif

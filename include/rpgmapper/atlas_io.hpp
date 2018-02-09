/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_IO_HPP
#define RPGMAPPER_MODEL_ATLAS_IO_HPP

#include <QFile>
#include <QStringList>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/reader_result.hpp>


namespace rpgmapper {
namespace model {


class AtlasIO {

public:

    AtlasIO() = default;

    ReaderResult read(QFile & file) const;
    WriterResult write(AtlasPointer & atlas, QFile & file) const;
};


}
}

#endif

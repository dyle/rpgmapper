/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_IO_ATLAS_IO_HPP
#define RPGMAPPER_MODEL_IO_ATLAS_IO_HPP

#include <QFile>
#include <QStringList>

#include <rpgmapper/io/reader_result.hpp>
#include <rpgmapper/io/writer_result.hpp>
#include <rpgmapper/atlas.hpp>


namespace rpgmapper {
namespace model {
namespace io {


/**
 * The Atlas I/O class can write and read a whole atlas to / from a file.
 */
class AtlasIO {

public:

    /**
     * Constrcutor.
     */
    AtlasIO() = default;

    /**
     * Reads atlas structure from a file.
     *
     * TODO: needs rather a sessoin object not an atlas
     *
     * @param   file        the file to read from.
     * @return  The whole read result including the atlas, content and other data.
     */
    ReaderResult read(QFile & file) const;
    
    /**
     * Writes an atlas to a file.
     *
     * TODO: needs rather a sessoin object not an atlas
     *
     * @param   atlas       the atlas to write.
     * @param   file        the file to write to.
     * @return  The result of the write operation.
     */
    WriterResult write(QSharedPointer<rpgmapper::model::Atlas> & atlas, QFile & file) const;
};


}
}
}

#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_WRITER_HPP
#define RPGMAPPER_MODEL_ATLAS_WRITER_HPP

#include <QFile>
#include <QStringList>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/operation_result.hpp>


namespace rpgmapper {
namespace model {

class AtlasWriter {

public:

    AtlasWriter() = default;

    OperationResult write(Atlas & atlas, QFile & file) const;

};


}
}

#endif

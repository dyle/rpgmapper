
/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_IO_CONTENT_HPP
#define RPGMAPPER_MODEL_IO_CONTENT_HPP

#include <map>

#include <QByteArray>
#include <QStringList>


namespace rpgmapper {
namespace model {
namespace io {


/**
 * A content (for input/output) is a map of named BLOBs.
 */
using Content = std::map<QString, QByteArray>;


}
}
}


#endif

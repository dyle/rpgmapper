/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_FILESYSTEM_HPP
#define RPGMAPPER_MODEL_FILESYSTEM_HPP


#include <QDir>

namespace rpgmapper {
namespace model {


QDir getApplicationDataSystemPath();

QDir getApplicationDataUserPath();


}
}


#endif

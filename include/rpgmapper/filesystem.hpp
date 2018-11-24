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


// TODO: switch to QStandardPaths

/**
 * This is the system path of all installed shared files of the rpgmapper.
 *
 * @return  The path to the installed shared files of the rpgmapper.
 */
QDir getApplicationDataSystemPath();


/**
 * Returns the path to the local user data files of the rpgmapper.
 *
 * @return  The path into the user's home used for local rpgmapper files.
 */
QDir getApplicationDataUserPath();


}
}


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_ATLAS_POINTER_HPP
#define RPGMAPPER_MODEL_ATLAS_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper::model {


// fwd
class Atlas;


/**
 * A smart pointer to a single atlas.
 */
using AtlasPointer = QSharedPointer<Atlas>;


}


#endif

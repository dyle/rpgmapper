/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGION_POINTER_HPP
#define RPGMAPPER_MODEL_REGION_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper::model {


// fwd
class Region;


/**
 * A smart pointer to a single region.
 */
using RegionPointer = QSharedPointer<Region>;


}


#endif

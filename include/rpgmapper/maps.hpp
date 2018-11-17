/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_MAPS_HPP
#define RPGMAPPER_MODEL_MAPS_HPP

#include <map>

#include <QString>

#include <rpgmapper/map_pointer.hpp>


namespace rpgmapper {
namespace model {


using Maps = std::map<QString, MapPointer>;


}
}


#endif

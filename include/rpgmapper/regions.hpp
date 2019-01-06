/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGIONS_HPP
#define RPGMAPPER_MODEL_REGIONS_HPP

#include <map>

#include <QString>

#include <rpgmapper/region_pointer.hpp>


namespace rpgmapper {
namespace model {


using Regions = std::map<QString, RegionPointer>;


}
}


#endif

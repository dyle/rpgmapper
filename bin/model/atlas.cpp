/*
 * atlas.cpp
 *
 * A RPG atlas
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// ------------------------------------------------------------
// incs

// rpgmappger
#include "common_macros.h"
#include "atlas.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {


/**
 * Internal data of an Atlas object.
 */
class Atlas::Atlas_data {

public:

    Atlas_data() : m_nRegionIdCounter(0) {
    }

    Regions m_cRegions;                 /**< all the regions managed by this Atlas */
    unsigned int m_nRegionIdCounter;    /**< region id counter */
};


}
}


// ------------------------------------------------------------
// code


/**
 * ctor
 */
Atlas::Atlas() : Nameable() {
    d = std::shared_ptr<Atlas::Atlas_data>(new Atlas::Atlas_data);
    name("New atlas");
}


/**
 * dtor
 */
Atlas::~Atlas() {
}


/**
 * make a deep copy of this Atlas
 *
 * @return  a new deep copied instance
 */
Atlas Atlas::clone() const {
    // TODO
    return Atlas();
}


/**
 * Creates a new region to this atlas
 *
 * @return  a reference to the new region
 */
Region & Atlas::createRegion() {

    d->m_nRegionIdCounter += 1;
    d->m_cRegions.emplace(d->m_nRegionIdCounter, Region());

    Region & region = d->m_cRegions[d->m_nRegionIdCounter];
    region.name("New Region " + std::to_string(d->m_nRegionIdCounter));

    return region;
}


/**
 * Check if the data needs to be saved.
 *
 * @return  true, if the data has to be saved.
  */
bool Atlas::needSave() const {

    // a save is needed if at least a single data
    // particle has been changed

    if (changed()) {
        return true;
    }

    for (auto const & region: regions()) {

        if (region.second.changed()) {
            return true;
        }

        for (auto const & map: region.second.maps()) {
            if (map.second.changed()) {
                return true;
            }
        }
    }

    return false;
}


/**
 * return all the regions managed in this region
 *
 * @return  all regions of this region
 */
Regions const & Atlas::regions() const {
    return d->m_cRegions;
}


/**
 * Enforce that no save is yet needed.
 */
void Atlas::resetSave() {

    // a save is needed, when at least a single
    // data particle has changed
    // TODO
    // for (auto & region: d->m_cRegions()) {
    //     region.second.changed(false);
    //     for (auto & map: region.second.maps()) {
    //         map.second.changed(false);
    //     }
    // }
}

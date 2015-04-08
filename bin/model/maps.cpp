/*
 * maps.cpp
 *
 * A collection of maps
 * 
 * Copyright (C) 2015, Oliver Maurhart, <dyle@dyle.org>
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

#include <algorithm>

// rpgmapper
#include "maps.h"

using namespace rpg;


// ------------------------------------------------------------
// code



/**
 * get a flat set of all known maps
 *
 * @return  a set of all known maps (w/o group stuff)
 */
rpg::mapset maps::map_set() {

    rpg::mapset res;
    for (auto cMapGroupIter = begin(); cMapGroupIter != end(); cMapGroupIter++) {
        rpg::mapset & cMapSet = (*cMapGroupIter).second;
        res.insert(cMapSet.begin(), cMapSet.end());
    }

    return res;
}


/**
 * erase a map
 *
 * remove map from the structure (w/o delete the resources)
 *
 * @param   sName           name of the map to retrieve
 * @return  true, if the map has been found and erased
 */
bool maps::erase_map(QString const & sName) {

    bool bErased = false;

    for (auto cMapGroupIter = begin(); cMapGroupIter != end() && !bErased; cMapGroupIter++) {

        rpg::mapset & cMaps = (*cMapGroupIter).second;
        auto cMapIter = std::find_if(cMaps.begin(), cMaps.end(), [&](rpg::map * m)->bool{ return (m->name() == sName); });
        if (cMapIter != cMaps.end()) {
            cMaps.erase(cMapIter);
            bErased = true;
        }
    }

    return bErased;
}


/**
 * return a map
 *
 * @param   name of the map to retrieve
 * @return  the map found (or nullptr if not)
 */
rpg::map * maps::find_map(QString const & sName) {
    
    for (auto cMapGroupIter = begin(); cMapGroupIter != end(); cMapGroupIter++) {
        rpg::map * cMap = find_map((*cMapGroupIter).first, sName);
        if (cMap != nullptr) return cMap;
    }

    return nullptr;
}


/**
 * return a map
 *
 * @param   sGroupName      name of the map group
 * @param   sName           name of the map to retrieve
 * @return  the map found (or nullptr if not)
 */
rpg::map * maps::find_map(QString const & sGroupName, QString const & sName) {

    auto cMapGroupIter = find(sGroupName);
    if (cMapGroupIter == end()) return nullptr;

    rpg::mapset & cMaps = (*cMapGroupIter).second;
    auto cMapIter = std::find_if(cMaps.begin(), cMaps.end(), [&](rpg::map * m)->bool{ return (m->name() == sName); });
    if (cMapIter != cMaps.end()) {
        return *cMapIter;
    }

    return nullptr;
}


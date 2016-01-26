/*
 * maps.cpp
 *
 * A collection of maps
 * 
 * Copyright (C) 2015, 2016 Oliver Maurhart, <dyle@dyle.org>
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
 * return a map
 *
 * @param   name of the map to retrieve
 * @return  the map found (or nullptr if not)
 */
rpg::map_ptr maps::find_map(QString const & sName) {
    
    for (auto cMapGroupIter = begin(); cMapGroupIter != end(); cMapGroupIter++) {
        rpg::map_ptr cMap = find_map((*cMapGroupIter).first, sName);
        if (cMap != nullptr) return cMap;
    }

    return rpg::map_ptr(nullptr);
}


/**
 * return a map
 *
 * @param   sGroupName      name of the map group
 * @param   sName           name of the map to retrieve
 * @return  the map found (or nullptr if not)
 */
rpg::map_ptr maps::find_map(QString const & sGroupName, QString const & sName) {

    auto cMapGroupIter = find(sGroupName);
    if (cMapGroupIter == end()) return rpg::map_ptr(nullptr);

    rpg::mapset & cMaps = (*cMapGroupIter).second;
    auto cMapIter = std::find_if(cMaps.begin(), cMaps.end(), [&](rpg::map_ptr const & m)->bool{ return (m->name() == sName); });
    if (cMapIter != cMaps.end()) {
        return *cMapIter;
    }

    return rpg::map_ptr(nullptr);
}


/**
 * remove a map
 *
 * @param   sName           name of the map to retrieve
 * @return  the map removed
 */
rpg::map_ptr maps::remove_map(QString const & sName) {

    rpg::map_ptr cMap = rpg::map_ptr(nullptr);

    for (auto cMapGroupIter = begin(); cMapGroupIter != end() && !cMap; cMapGroupIter++) {

        rpg::mapset & cMaps = (*cMapGroupIter).second;
        auto cMapIter = std::find_if(cMaps.begin(), cMaps.end(), [&](rpg::map_ptr const & m)->bool{ return (m->name() == sName); });
        if (cMapIter != cMaps.end()) {
            cMap = *cMapIter;
            cMaps.erase(cMapIter);
        }
    }

    return cMap;
}

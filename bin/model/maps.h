/*
 * maps.h
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


#ifndef __MODEL_MAPS_H
#define __MODEL_MAPS_H


// ------------------------------------------------------------
// incs

#include <map>
#include <string>


// rpgmapper
#include "map.h"


// ------------------------------------------------------------
// decl


namespace rpg {


/**
 * a somehow clever colletion of maps
 */
class maps : public std::map<std::string, rpg::mapset> {


public:


    /**
     * get a flat set of all known maps
     *
     * @return  a set of all known maps (w/o group stuff)
     */
    rpg::mapset map_set();


    /**
     * erase a map
     *
     * remove map from the structure (w/o delete the resources)
     *
     * @param   sName           name of the map to retrieve
     * @return  true, if the map has been found and erased
     */
    bool erase_map(std::string const & sName);


    /**
     * return a map
     *
     * @param   sName           name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map * find_map(std::string const & sName);


    /**
     * return a map
     *
     * @param   sGroupName      name of the map group
     * @param   sName           name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map * find_map(std::string const & sGroupName, std::string const & sName);

};


}


#endif


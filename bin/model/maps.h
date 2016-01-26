/*
 * maps.h
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
 * a colletion of maps based on a group name
 * 
 * The group name is though to group maps tightly related to
 * each other. E.g. the Group "Tower of Doom" might have several
 * maps attached to it. The first might be the entrance level
 * and then higher up the other maps following.
 * 
 * However, all maps ought to have a unique name without respect
 * to the group name there are attached to.
 */
class maps : public std::map<QString, rpg::mapset> {


public:


    /**
     * get a flat set of all known maps
     *
     * @return  a set of all known maps
     */
    rpg::mapset map_set();


    /**
     * return a map
     *
     * @param   sName           name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map_ptr find_map(QString const & sName);


    /**
     * return a map
     *
     * @param   sGroupName      name of the map group
     * @param   sName           name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map_ptr find_map(QString const & sGroupName, QString const & sName);
    

    /**
     * remove a map
     *
     * @param   sName           name of the map to retrieve
     * @return  the map removed
     */
    rpg::map_ptr remove_map(QString const & sName);
    
};


}


#endif


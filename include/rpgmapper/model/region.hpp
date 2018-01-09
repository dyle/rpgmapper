/*
 * region.hpp
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


#ifndef MODEL_REGION_H
#define MODEL_REGION_H


// ------------------------------------------------------------
// incs

#include <map>
#include <memory>
#include <string>

// rpgmapper
#include "nameable.hpp"
#include "map.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A colletion of maps based on a name.
 *
 * Note: copy an Region instance is shallow. For a deep copy use the "clone()" method.
 */
class Region : public Nameable {


public:


    /**
     * ctor
     */
    Region();


    /**
     * dtor
     */
    virtual ~Region();


    /**
     * check if the region or any aggregated objects changed.
     *
     * @return  true if the region or any dependend object changed.
     */
    virtual bool changedAccumulated() const;


    /**
     * set the change flag of the region and any dependend objects
     *
     * @param   bChanged        the new changed information
     */
    virtual void changedAccumulated(bool bChanged);


    /**
     * make a deep copy of this Atlas
     *
     * @return  a new deep copied instance
     */
    Region clone() const;


    /**
     * Creates a new Map to this region
     *
     * @return  a reference to the new Map
     */
    Map & createMap();


    /**
     * return all the maps managed in this region
     *
     * @return  all maps of this region
     */
    Maps const & maps() const;


private:


    class Region_data;                              /**< internal data type */
    std::shared_ptr<Region::Region_data> d;         /**< internal data instance */

};


/**
 * multiple regions indexed by a string (id)
 */
typedef std::map<unsigned int, Region> Regions;


}
}


#endif

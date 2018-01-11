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

#include <QJsonObject>

// rpgmapper
#include "nameable.hpp"
#include "map.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


class Atlas;


/**
 * A collection of maps based on a name.
 *
 * Note: copy an Region instance is shallow. For a deep copy use the "clone()" method.
 */
class Region : public Nameable {


    friend class Atlas;


public:


    /**
     * type of a region's ID
     */
    typedef int id_t;


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
     * @return  true if the region or any dependent object changed.
     */
    virtual bool changedAccumulated() const;


    /**
     * set the change flag of the region and any dependent objects
     *
     * @param   bChanged        the new changed information
     */
    virtual void changedAccumulated(bool bChanged);


    /**
     * make a deep copy of this region
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
     * return the id of the region
     *
     * @return  the id of the region
     */
    id_t id() const { return m_nId; }


    /**
     * load the region from json
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON);


    /**
     * get map by id
     *
     * @param   nId         id of the map to get
     * @return  map instance
     */
    Map & map(Map::id_t nId);


    /**
     * get map by id
     *
     * @param   nId         id of the map to get
     * @return  map instance
     */
    Map const & map(Map::id_t nId) const;


    /**
     * return all the maps managed in this region
     *
     * @return  all maps of this region
     */
    Maps const & maps() const;


    /**
     * means to order this region among other regions
     *
     * @return  a value indicating the position of this region among others
     */
    int orderValue() const;


    /**
     * set the means to order this region among other regions
     *
     * @param   nOrderValue     a value indicating the position of this region among others
     */
    void orderValue(int nOrderValue);


    /**
     * save the region to json
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const;


private:


    /**
     * reset the region to empty state
     */
    void clear();


    /**
     * set a new id to the region
     *
     * @param   nId         the new id of the region
     */
    void id(id_t nId) { m_nId = nId; }


    id_t m_nId;                                     /**< region id */

    class Region_data;                              /**< internal data type */
    std::shared_ptr<Region::Region_data> d;         /**< internal data instance */

};


/**
 * multiple regions
 */
typedef std::map<Region::id_t, Region> Regions;


}
}


#endif

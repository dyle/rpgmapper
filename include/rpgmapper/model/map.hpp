/*
 * map.hpp
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


#ifndef MODEL_MAP_H
#define MODEL_MAP_H


// ------------------------------------------------------------
// incs


#include <map>
#include <memory>
#include <string>

#include <QJsonObject>

// rpgmapper
#include "nameable.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


class Region;


/**
 * A single rpg Map.
 *
 * Note: copy an Map instance is shallow. For a deep copy use the "clone()" method.
 */
class Map : public Nameable {


    friend class Region;


public:


    /**
     * type of a map's ID
     */
    typedef int id_t;


    /**
     * ctor
     */
    Map();


    /**
     * dtor
     */
    virtual ~Map();


    /**
     * make a deep copy of this Map
     *
     * @return  a new deep copied instance
     */
    Map clone() const;


    /**
     * return the id of the map
     *
     * @return  the id of the map
     */
    id_t id() const { return m_nId; }


    /**
     * load the map from json
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON);


    /**
     * means to order this map among other maps
     *
     * @return  a value indicating the position of this map among others
     */
    int orderValue() const;


    /**
     * set the means to order this map among other maps
     *
     * @param   nOrderValue     a value indicating the position of this maps among others
     */
    void orderValue(int nOrderValue);


    /**
     * save the map to json
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const;


private:


    /**
     * reset the map to empty state
     */
    void clear();


    /**
     * set a new id to the maps
     *
     * @param   nId         the new id of the map
     */
    void id(id_t nId) { m_nId = nId; }


    id_t m_nId;                                 /**< map id */
    class Map_data;                             /**< internal data type */
    std::shared_ptr<Map::Map_data> d;           /**< internal data instance */
};


/**
 * multiple maps
 */
typedef std::map<Map::id_t, Map> Maps;


}
}


#endif

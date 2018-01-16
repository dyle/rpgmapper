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


#ifndef MODEL_MAP_HPP
#define MODEL_MAP_HPP


// ------------------------------------------------------------
// incs


#include <map>
#include <memory>

#include <QSharedPointer>

// rpgmapper
#include "nameable.hpp"
#include "types.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A single rpg Map.
 *
 * Note: copy an Map instance is shallow. For a deep copy use the "clone()" method.
 */
class Map : public Nameable {


    Q_OBJECT


public:


    /**
     * Type of a map's ID.
     */
    typedef int id_t;


    /**
     * Create a new map (factory method).
     *
     * @param   cAtlas      parent object
     * @param   nId         the id of the new map (id < 0 a new will be assigned)
     * @return  a new map
     */
    static MapPointer create(Atlas * cAtlas, id_t nId = -1);


    /**
     * Return the id of the map.
     *
     * @return  the id of the map
     */
    id_t id() const { return m_nId; }


    /**
     * Load the map from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


    /**
     * Means to order this map among other maps.
     *
     * @return  a value indicating the position of this map among others
     */
    int orderValue() const;


    /**
     * Set the means to order this map among other maps.
     *
     * @param   nOrderValue     a value indicating the position of this maps among others
     */
    void orderValue(int nOrderValue);


    /**
     * Save the map to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


public slots:


    /**
     * Reset the map to an empty state.
     */
    void clear();


signals:


    /**
     * The id of the map changed.
     *
     * @param   nOldId      the old id
     */
    void changedId(id_t nOldId);


private:


    /**
     * Ctor.
     *
     * @param   cAtlas      parent object
     * @param   nId         id of the map
     */
    explicit Map(Atlas * cAtlas, Map::id_t nId);


    id_t m_nId;                                 /**< map id */
    class Map_data;                             /**< internal data type */
    std::shared_ptr<Map::Map_data> d;           /**< internal data instance */
};


/**
 * Multiple maps.
 */
typedef std::map<Map::id_t, MapPointer> Maps;


}
}


#endif

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


#ifndef MODEL_REGION_HPP
#define MODEL_REGION_HPP


// ------------------------------------------------------------
// incs

#include <map>
#include <memory>

#include <QJsonObject>
#include <QSharedPointer>

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

    Q_OBJECT

    friend class Atlas;


public:


    /**
     * Type of a region's ID.
     */
    typedef int id_t;


    /**
     * Ctor.
     *
     * @param   cParent     parent object
     */
    explicit Region(QObject * cParent = nullptr);


    /**
     * Creates a new Map to this region
     *
     * @return  a reference to the new Map
     */
    MapPointer createMap();


    /**
     * Return the id of the region.
     *
     * @return  the id of the region
     */
    id_t id() const { return m_nId; }


    /**
     * Load the region from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


    /**
     * Return all the maps managed in this region.
     *
     * @return  all maps of this region
     */
    Maps const & maps() const;


    /**
     * State if the region (and any descendants) has changed.
     *
     * @return  true, if the region (or any descendants) has changed.
     */
    bool modified() const override;


    /**
     * Set the region and all descendants to a new modification state.
     *
     * @param   bModified       the new modification state
     */
    void modified(bool bModified) override;


    /**
     * Means to order this region among other regions.
     *
     * @return  a value indicating the position of this region among others
     */
    int orderValue() const;


    /**
     * Set the means to order this region among other regions.
     *
     * @param   nOrderValue     a value indicating the position of this region among others
     */
    void orderValue(int nOrderValue);


    /**
     * Save the region to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


public slots:


    /**
     * Reset the region to empty state.
     */
    void clear();


private:


    /**
     * Set a new id to the region.
     *
     * @param   nId         the new id of the region
     */
    void id(id_t nId) { m_nId = nId; }


    id_t m_nId;                                     /**< region id */

    class Region_data;                              /**< internal data type */
    std::shared_ptr<Region::Region_data> d;         /**< internal data instance */

};


/**
 * Smart pointer to a region.
 */
typedef QSharedPointer<Region> RegionPointer;


/**
 * multiple regions
 */
typedef std::map<Region::id_t, RegionPointer> Regions;


}
}


#endif

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

// rpgmapper
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A collection of maps based on a name.
 */
class Region : public Nameable {


    Q_OBJECT


public:


    /**
     * Create a new region (factory method).
     *
     * @param   cAtlas      parent object
     * @param   nId         the id of the new region (id < 0 a new will be assigned)
     * @return  a new region
     */
    static RegionPointer create(Atlas * cAtlas, regionid_t nId = -1);


    /**
     * Adds a map to this region.
     *
     * @param   cMap    the map to add.
     */
    void addMap(MapPointer cMap);


    /**
     * Return the id of the region.
     *
     * @return  the id of the region
     */
    regionid_t id() const { return m_nId; }


    /**
     * Load the region from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


    /**
     * Get all maps of this region.
     *
     * @return  The maps of this region.
     */
    Maps maps() const;


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
     * Reset the region to an empty state.
     */
    void clear();


private slots:


    /**
     * A map changed its Id.
     *
     * @param   nOldId              old id of the map
     */
    void changedMapId(mapid_t nOldId);


    /**
     * A map changed its region.
     *
     * @param   nOldRegionId        id of the old region
     */
    void changedMapRegion(regionid_t nOldRegionId);


signals:


    /**
     * A map has been added to this region.
     *
     * @param   cMap        the map added
     */
    void addedMap(MapPointer cMap);


    /**
     * The id of the region changed.
     *
     * @param   nOldId      the old id
     */
    void changedId(regionid_t nOldId);


    /**
     * A map has been removed from this region.
     *
     * @param   cMap        the map removed
     */
    void removedMap(MapPointer cMap);


private:


    /**
     * Ctor.
     *
     * @param   cAtlas      parent object
     * @param   nId     id of the region
     */
    explicit Region(Atlas * cAtlas, regionid_t nId);


    /**
     * Get our own smart pointer as hold by the governing atlas.
     *
     * @return  a smart pointer to our own instance derived from the atlas.
     */
    RegionPointer self();


    regionid_t m_nId;                               /**< Region id. */
    class Region_data;                              /**< Internal data type. */
    std::shared_ptr<Region::Region_data> d;         /**< Internal data instance. */

};


}
}


#endif

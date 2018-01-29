/*
 * atlas.hpp
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


#ifndef MODEL_ATLAS_HPP
#define MODEL_ATLAS_HPP


// ------------------------------------------------------------
// incs

#include <iostream>
#include <memory>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

// rpgmapper
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A single atlas holds regions with maps each.
 */
class Atlas : public Nameable {


    Q_OBJECT


public:


    /**
     * Ctor.
     *
     * @param   cParent     parent object
     */
    explicit Atlas(QObject * cParent = nullptr);


    /**
     * Creates a new map to this atlas.
     *
     * @return  a reference to the new map
     */
    MapPointer createMap();


    /**
     * Creates a new region to this atlas.
     *
     * @return  a reference to the new region
     */
    RegionPointer createRegion();


    /**
     * Returnes the currenty selected Map.
     *
     * @return  the map which is currently selected
     */
    MapPointer & currentMap();


    /**
     * Returns the currently selected Region.
     *
     * @return  the region which is currently selected
     */
    RegionPointer & currentRegion();


    /**
     * Dumps the current atlas structure to a string.
     *
     * @return  a string describing the current structure
     */
    std::string dumpStructure() const;


    /**
     * Create a json string form this atlas.
     *
     * @param   eJsonFormat     the format for representation
     * @return  a string holding the atlas in json format
     */
    QString json(QJsonDocument::JsonFormat eJsonFormat = QJsonDocument::Indented) const;


    /**
     * Load the atlas from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


    /**
     * Return all the maps managed by this atlas.
     *
     * @return  all maps of this atlas
     */
    Maps const & maps() const;


    /**
     * State if the atlas (and any descendants) has changed.
     *
     * @return  true, if the atlas (or any descendants) has changed.
     */
    bool isModified() const override;


    /**
     * Get a map based on an Id.
     *
     * Hence, if the map has not been found, a MapPointer
     * with data() == nullptr is returned,
     *
     * @param   nMapId          id of the map
     * @return  a smart map pointer
     */
    MapPointer & mapById(rpgmapper::model::mapid_t nMapId);


    /**
     * Get a map based on an Id.
     *
     * Hence, if the map has not been found, a MapPointer
     * with data() == nullptr is returned,
     *
     * @param   nMapId          id of the map
     * @return  a smart map pointer
     */
    MapPointer const & mapById(rpgmapper::model::mapid_t nMapId) const;


    /**
     * Get a region based on an Id.
     *
     * Hence, if the region has not been found, a RegionPointer
     * with data() == nullptr is returned,
     *
     * @param   nRegionId       id of the region
     * @return  a smart region pointer
     */
    RegionPointer & regionById(rpgmapper::model::regionid_t nRegionId);


    /**
     * Get a region based on an Id.
     *
     * Hence, if the region has not been found, a RegionPointer
     * with data() == nullptr is returned,
     *
     * @param   nRegionId       id of the region
     * @return  a smart region pointer
     */
    RegionPointer const & regionById(rpgmapper::model::regionid_t nRegionId) const;


    /**
     * Return all the regions managed by this atlas.
     *
     * @return  all regions of this atlas
     */
    Regions const & regions() const;


    /**
     * Save the atlas to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


    /**
     * Set the atlas and all descendants to a new modification state.
     * Only applies "true" to the current item and not to all maps and regions.
     *
     * @param   bModified       the new modification state
     */
    void setModified(bool bModified) override;


public slots:


    /**
     * Deletes a map.
     *
     * @param   nMapId          the map to delete
     */
    void deleteMap(rpgmapper::model::mapid_t nMapId);


    /**
     * Deletes a region.
     *
     * @param   nRegionId       the region to delete
     */
    void deleteRegion(rpgmapper::model::regionid_t nRegionId);


    /**
     * Set a new map as selected.
     * An invalid id (e.g. -1) will select no map.
     *
     * @param   nMapId      the map selected
     */
    void setCurrentMap(rpgmapper::model::mapid_t nMapId);


    /**
     * Select a new region as current.
     * An invalid id (e.g. -1) will select no region.
     *
     * @param   nRegionId   the region selected
     */
    void setCurrentRegion(rpgmapper::model::regionid_t nRegionId);


private slots:


    /**
     * A map has changed its name.
     */
    void mapChangedName();


    /**
     * A region has changed its name.
     */
    void regionChangedName();


signals:


    /**
     * The atlas has been modified.
     */
    void changedAtlas();


    /**
     * A map has changed its name.
     *
     * @param   nMapId          the id of the map changed
     */
    void changedMapName(rpgmapper::model::mapid_t nMapId);


    /**
     * A region has changed its name.
     *
     * @param   nRegionId       the id of the region changed
     */
    void changedRegionName(rpgmapper::model::regionid_t nRegionId);


    /**
     * A map has been deleted.
     *
     * @param   nMapId      id of the map deleted
     */
    void deletedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * A region has been deleted.
     *
     * @param nRegionId     id of the region deleted
     */
    void deletedRegion(rpgmapper::model::regionid_t nRegionId);


    /**
     * We have a new map.
     *
     * @param   nMapId      id of the new map
     */
    void newMap(rpgmapper::model::mapid_t nMapId);


    /**
     * We have a new region.
     *
     * @param nRegionId     id of the new region
     */
    void newRegion(rpgmapper::model::regionid_t nRegionId);


    /**
     * Selected a map.
     *
     * @param   nMapId      id of the newly selected map
     */
    void selectedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * Selected a region.
     *
     * @param   nRegionId   id of the newly selected region
     */
    void selectedRegion(rpgmapper::model::regionid_t cRegionId);


private:


    /**
     * Reset the atlas to an empty state.
     */
    void clear();


    /**
     * Provide some nice initial state.
     */
    void init();


    class Atlas_data;                               /**< internal data type */
    std::shared_ptr<Atlas::Atlas_data> d;           /**< internal data instance */

};


}
}


#endif

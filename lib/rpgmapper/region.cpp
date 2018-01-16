/*
 * region.cpp
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


// ------------------------------------------------------------
// incs

#include <set>
#include <QDebug>
#include <QJsonArray>

// rpgmapper
#include <rpgmapper/common_macros.h>
#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {


/**
 * Internal data of a Region object.
 */
class Region::Region_data {

public:

    Region_data() = default;

    Atlas * m_cAtlas = nullptr;         /**< Parent atlas back pointer. */
    std::set<mapid_t> m_cMaps;          /**< All the associated maps of this region. */
    int m_nOrderValue = 0;              /**< Means to order a region among others */
};


/**
 * Global region id counter.
 */
static regionid_t g_nRegionIdCounter = 0;


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cAtlas      parent object
 * @param   nId     id of the region
 */
Region::Region(Atlas * cAtlas, regionid_t nId) : Nameable(cAtlas), m_nId(nId) {

    Q_ASSERT(cAtlas);

    d = std::make_shared<Region::Region_data>();
    d->m_cAtlas = cAtlas;
    name("New Region " + QString::number(id()));
}


/**
 * Adds a map to this region.
 *
 * @param   cMap    the map to add.
 */
void Region::addMap(MapPointer cMap) {

    if (d->m_cMaps.find(cMap->id()) == d->m_cMaps.end()) {
        d->m_cMaps.insert(cMap->id());
        cMap->region(self());
        connect(cMap.data(), &Map::changedId, this, &Region::changedMapId);
        emit addedMap(cMap);
    }
}


/**
 * A map changed its Id.
 *
 * @param   nOldId      Old id of the map
 */
void Region::changedMapId(mapid_t nOldId) {
    d->m_cMaps.erase(nOldId);
    auto * cMap = dynamic_cast<Map *>(QObject::sender());
    if (cMap) {
        d->m_cMaps.insert(cMap->id());
    }
}


/**
 * Reset the region to an empty state.
 */
void Region::clear() {
    name("");
}


/**
 * Create a new region (factory method).
 *
 * @param   cAtlas      parent object
 * @param   nId         the id of the new region (id < 0 a new will be assigned)
 * @return  a new region
 */
RegionPointer Region::create(Atlas * cAtlas, regionid_t nId) {
    nId = nId < 0 ? ++g_nRegionIdCounter : nId;
    return RegionPointer(new Region(cAtlas, nId), &Region::deleteLater);
}


/**
 * Load the region from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Region::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    auto nId = id();
    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        m_nId = cJSON["id"].toInt();
        g_nRegionIdCounter = std::max(g_nRegionIdCounter, m_nId);
    }
    if (cJSON.contains("orderValue") && cJSON["orderValue"].isDouble()) {
        orderValue(cJSON["orderValue"].toInt());
    }

    if (nId != id()) {
        emit changedId(nId);
    }
}


/**
 * Get all maps of this region.
 *
 * @return  The maps of this region.
 */
Maps Region::maps() const {

    Maps cMaps;
    std::for_each(d->m_cMaps.begin(),
                  d->m_cMaps.end(),
                  [&] (mapid_t nId) { cMaps.insert(std::make_pair(nId, d->m_cAtlas->maps()[nId])); });
    return cMaps;
}


/**
 * Means to order this region among other regions.
 *
 * @return  a value indicating the position of this region among others
 */
int Region::orderValue() const {
    return d->m_nOrderValue;
}


/**
 * Set the means to order this region among other regions.
 *
 * @param   nOrderValue     a value indicating the position of this region among others
 */
void Region::orderValue(int nOrderValue) {
    if (d->m_nOrderValue == nOrderValue) {
        return;
    }
    d->m_nOrderValue = nOrderValue;
    modified(true);
}


/**
 * Removes a map from this region.
 *
 * @param   cMap    the map to remove.
 */
void Region::removeMap(MapPointer cMap) {

    auto iter = d->m_cMaps.find(cMap->id());
    if (iter != d->m_cMaps.end()) {
        d->m_cMaps.erase(iter);
        disconnect(cMap.data(), &Map::changedId, this, &Region::changedMapId);
        emit removedMap(cMap);
    }
}


/**
 * Save the region to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Region::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["orderValue"] = orderValue();
}


/**
 * Get our own smart pointer as hold by the governing atlas.
 *
 * @return  a smart pointer to our own instance derived from the atlas.
 */
RegionPointer Region::self() {
    return d->m_cAtlas->regions()[id()];
}


/**
 * Get our own smart pointer as hold by the governing atlas.
 *
 * @return  a smart pointer to our own instance derived from the atlas.
 */
RegionPointer const Region::self() const {
    return d->m_cAtlas->regions()[id()];
}

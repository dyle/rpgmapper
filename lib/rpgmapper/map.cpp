/*
 * map.cpp
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

// rpgmapper
#include <rpgmapper/atlas.hpp>


using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {


/**
 * Internal data of a Map object.
 */
class Map::Map_data {

public:

    Map_data() = default;

    Atlas * m_cAtlas = nullptr;                 /**< Parent atlas back pointer. */
    int m_nOrderValue = 0;                      /**< Means to order a map among others. */
    regionid_t m_nRegionId = -1;                /**< Id of the region of this map. */
};


/**
 * Global map id counter.
 */
static mapid_t g_nMapIdCounter = 0;


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cAtlas      parent object
 * @param   nId     id of the map
 */
Map::Map(Atlas * cAtlas, mapid_t nId) : Nameable(cAtlas), m_nId(nId) {
    Q_ASSERT(cAtlas);
    d = std::make_shared<Map::Map_data>();
    d->m_cAtlas = cAtlas;
    name("New map " + QString::number(id()));
}


/**
 * Reset the region to an empty state.
 */
void Map::clear() {
    name("");
}


/**
 * Create a new map (factory method).
 *
 * @param   cAtlas      parent object
 * @param   nId         the id of the new map (id < 0 a new will be assigned)
 * @return  a new map
 */
MapPointer Map::create(Atlas * cAtlas, mapid_t nId) {
    nId = nId < 0 ? ++g_nMapIdCounter : nId;
    return MapPointer(new Map(cAtlas, nId), &Map::deleteLater);
}


/**
 * Load the map from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Map::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    auto nId = id();
    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        m_nId = cJSON["id"].toInt();
        g_nMapIdCounter = std::max(g_nMapIdCounter, m_nId);
    }

    if (cJSON.contains("orderValue") && cJSON["orderValue"].isDouble()) {
        orderValue(cJSON["orderValue"].toInt());
    }

    if (nId != id()) {
        emit changedId(nId);
    }
}


/**
 * Means to order this map among other maps.
 *
 * @return  a value indicating the position of this map among others
 */
int Map::orderValue() const {
    return d->m_nOrderValue;
}


/**
 * Set the means to order this map among other maps.
 *
 * @param   nOrderValue     a value indicating the position of this maps among others
 */
void Map::orderValue(int nOrderValue) {
    if (d->m_nOrderValue == nOrderValue) {
        return;
    }
    d->m_nOrderValue = nOrderValue;
    modified(true);
}


/**
 * Return the region to which this map belongs to.
 *
 * @return  the region of this map
 */
RegionPointer const Map::region() const {
    if (d->m_nRegionId < 0) {
        return RegionPointer(nullptr);
    }
    return d->m_cAtlas->regions()[d->m_nRegionId];
}


/**
 * Set the region this map belongs.
 *
 * @param   cRegion     the new region of this map
 */
void Map::region(RegionPointer cRegion) {

    auto nRegionId = cRegion->id();
    if (d->m_nRegionId == nRegionId) {
        return;
    }

    d->m_nRegionId = cRegion->id();
    cRegion->addMap(self());
    d->m_cAtlas->regions()[nRegionId]->removeMap(self());

    emit changedRegion();
}


/**
 * Save the map to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Map::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["orderValue"] = orderValue();
}


/**
 * Get our own smart pointer as hold by the governing atlas.
 *
 * @return  a smart pointer to our own instance derived from the atlas.
 */
MapPointer Map::self() {
    return d->m_cAtlas->maps()[id()];
}


/**
 * Get our own smart pointer as hold by the governing atlas.
 *
 * @return  a smart pointer to our own instance derived from the atlas.
 */
MapPointer const Map::self() const {
    return d->m_cAtlas->maps()[id()];
}

/*
 * setRegion.cpp
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

#include <cassert>
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
Region::Region(Atlas * cAtlas, regionid_t nId) : Nameable{cAtlas}, m_nId{nId} {

    if (cAtlas == nullptr) {
        throw std::invalid_argument("Atlas argument shall not be nullptr.");
    }

    d = std::make_shared<Region::Region_data>();
    d->m_cAtlas = cAtlas;
    d->m_nOrderValue = nId;

    init();
}


/**
 * Adds a map to this region.
 *
 * @param   cMap    the map to add.
 */
void Region::addMap(MapPointer cMap) {

    if (cMap.data() == nullptr) {
        throw std::invalid_argument("Map argument shall not be nullptr.");
    }

    if (d->m_cMaps.find(cMap->id()) == d->m_cMaps.end()) {

        d->m_cMaps.insert(cMap->id());
        cMap->setRegion(d->m_cAtlas->regionById(id()));
        connect(cMap.data(), &Map::changedRegion, this, &Region::changedMapRegion);

        emit addedMap(cMap->id());
    }
}


/**
 * A map changed its region.
 */
void Region::changedMapRegion() {

    auto * cMap = dynamic_cast<Map *>(QObject::sender());
    if (!cMap) {
        return;
    }
    auto nMapId = cMap->id();
    auto nRegionId = cMap->region()->id();

    if (nRegionId == id()) {
        addMap(d->m_cAtlas->mapById(nMapId));
    }
    else {
        if (d->m_cMaps.find(nMapId) != d->m_cMaps.end()) {
            removedMap(nMapId);
        }
    }


    // TODO
//    if (nOldRegionId == id()) {
//        addMap(d->m_cAtlas->maps()[nMapId]);
//        return;
//    }
//
//    auto nRegionId = cMap->region()->id();
//    if ((nOldRegionId == id()) && (d->m_cMaps.find(nMapId) != d->m_cMaps.end())) {
//
//        d->m_cMaps.erase(nMapId);
//
            // TODO
//        disconnect(cMap, &Map::changedRegion, this, &Region::changedMapRegion);
//
//        emit removedMap(d->m_cAtlas->maps()[nMapId]);
//    }
//
//    if ((nRegionId == id()) && (d->m_cMaps.find(nMapId) == d->m_cMaps.end())) {
//        addMap(d->m_cAtlas->maps()[nMapId]);
//    }

}


/**
 * Reset the region to an empty state.
 */
void Region::clear() {
    setName("");
}


/**
 * Create a new region (factory method).
 *
 * @param   cAtlas      parent object
 * @return  a new region
 */
RegionPointer Region::create(Atlas * cAtlas) {
    if (cAtlas == nullptr) {
        throw std::invalid_argument("Atlas argument shall not be nullptr.");
    }
    return RegionPointer{new Region{cAtlas, ++g_nRegionIdCounter}, &Region::deleteLater};
}


/**
 * Provide some nice initial state.
 */
void Region::init() {
    clear();
    setName("New Region " + QString::number(id()));
}


/**
 * Load the region from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Region::load(QJsonObject const & cJSON) {

    clear();
    Nameable::load(cJSON);

    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        m_nId = cJSON["id"].toInt();
        g_nRegionIdCounter = std::max(g_nRegionIdCounter, m_nId);
    }
    if (cJSON.contains("orderValue") && cJSON["orderValue"].isDouble()) {
        setOrderValue(cJSON["orderValue"].toInt());
    }

    if (cJSON.contains("maps") && cJSON["maps"].isArray()) {

        QJsonArray cJSONMaps = cJSON["maps"].toArray();
        for (auto && cJSONMapId : cJSONMaps) {
            if (cJSONMapId.isDouble()) {
                addMap(d->m_cAtlas->mapById(cJSONMapId.toInt()));
            }
        }
    }
}


/**
 * Load the region from json.
 *
 * @param   cJSON       the json instance to load from
 * @param   cAtlas      parent object
 * @return  the loaded region instance
 */
RegionPointer Region::load(QJsonObject const & cJSON, Atlas * cAtlas) {
    auto cRegion = RegionPointer{new Region{cAtlas, -1}, &Map::deleteLater};
    cRegion->load(cJSON);
    return cRegion;
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
                  [&] (mapid_t nId) { cMaps.insert(std::make_pair(nId, d->m_cAtlas->mapById(nId))); });
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
 * Save the region to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Region::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["orderValue"] = orderValue();

    QJsonArray cJSONMaps;
    for (auto nMapId: d->m_cMaps) {
        cJSONMaps.append(nMapId);
    }
    cJSON["maps"] = cJSONMaps;
}


/**
 * Set the means to order this region among other regions.
 *
 * @param   nOrderValue     a value indicating the position of this region among others
 */
void Region::setOrderValue(int nOrderValue) {

    if (d->m_nOrderValue == nOrderValue) {
        return;
    }
    d->m_nOrderValue = nOrderValue;
    setModified(true);
}

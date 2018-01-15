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

#include <QJsonArray>

// rpgmapper
#include <rpgmapper/region.hpp>

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

    Maps m_cMaps;                       /**< all the maps managed by this region */
    Map::id_t m_nMapIdCounter = 0;      /**< map id counter */
    int m_nOrderValue = 0;              /**< means to order a region among others */
};


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent     parent object
 */
Region::Region(QObject * cParent) : Nameable(cParent) {
    d = std::make_shared<Region::Region_data>();
    name("New Region");
    createMap();
}


/**
 * Reset the region to empty state.
 */
void Region::clear() {
    name("");
    d->m_cMaps.clear();
    d->m_nMapIdCounter = 0;
    modified(true);
}


/**
 * Creates a new Map to this region.
 *
 * @return  a reference to the new Map
 */
MapPointer Region::createMap() {

    d->m_nMapIdCounter += 1;
    auto cPair = d->m_cMaps.emplace(d->m_nMapIdCounter, MapPointer(new Map(), &Map::deleteLater));
    auto cMap = (*cPair.first).second;

    cMap->name("New Map " + QString::number(d->m_nMapIdCounter));
    cMap->id(d->m_nMapIdCounter);

    return cMap;
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
        id(cJSON["id"].toInt());
    }

    if (cJSON.contains("orderValue") && cJSON["orderValue"].isDouble()) {
        orderValue(cJSON["orderValue"].toInt());
    }

    if (cJSON.contains("maps") && cJSON["maps"].isArray()) {

        QJsonArray cJSONMaps = cJSON["maps"].toArray();
        for (auto && cJSONMap : cJSONMaps) {

            MapPointer cMap(new Map(), &Map::deleteLater);
            cMap->load(cJSONMap.toObject());

            auto nId = cMap->id();
            d->m_cMaps.insert(std::make_pair(nId, cMap));
            d->m_nMapIdCounter = std::max<Map::id_t>(nId, d->m_nMapIdCounter);
        }
    }
}


/**
 * Return all the maps managed in this region.
 *
 * @return  all maps of this region
 */
Maps const & Region::maps() const {
    return d->m_cMaps;
}


/**
 * State if the region (and any descendants) has changed.
 *
 * @return  true, if the region (or any descendants) has changed.
 */
bool Region::modified() const {
    if (Nameable::modified()) {
        return true;
    }
    // TODO: work on descendants
    return false;
}


/**
 * Set the region and all descendants to a new modification state.
 *
 * @param   bModified       the new modification state
 */
void Region::modified(bool bModified) {
    Nameable::modified(bModified);
    // TODO: work on descendants
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
 * Save the region to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Region::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["orderValue"] = orderValue();

    QJsonArray cJSONMaps;
    for (auto const & cMap: d->m_cMaps) {
        QJsonObject jo;
        cMap.second->save(jo);
        cJSONMaps.append(jo);
    }
    cJSON["maps"] = cJSONMaps;
}

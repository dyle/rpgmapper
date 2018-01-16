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

    int m_nOrderValue = 0;              /**< means to order a region among others */
};


/**
 * Global region id counter.
 */
static Region::id_t g_nRegionIdCounter = 0;


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent     parent object (should be an atlas instance)
 * @param   nId     id of the region
 */
Region::Region(QObject * cParent, Region::id_t nId) : Nameable(cParent), m_nId(nId) {
    d = std::make_shared<Region::Region_data>();
    name("New Region " + QString::number(id()));
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
 * @param   cParent     parent object (should be an atlas instance)
 * @param   nId         the id of the new region (id < 0 a new will be assigned)
 * @return  a new region
 */
RegionPointer Region::create(QObject * cParent, id_t nId) {
    nId = nId < 0 ? ++g_nRegionIdCounter : nId;
    return RegionPointer(new Region(cParent, nId), &Region::deleteLater);
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
}

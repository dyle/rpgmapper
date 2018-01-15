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
#include <rpgmapper/map.hpp>


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

    int m_nOrderValue = 0;              /**< means to order a map among others */

};


}
}


// ------------------------------------------------------------
// code


/**
 * ctor
 */
Map::Map() : Nameable() {
    d = std::make_shared<Map::Map_data>();
}


/**
 * reset the region to empty state
 */
void Map::clear() {
    name("");
    changed(true);
}


/**
 * load the map from json
 *
 * @param   cJSON       the json instance to load from
 */
void Map::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        id(cJSON["id"].toInt());
    }

    if (cJSON.contains("orderValue") && cJSON["orderValue"].isDouble()) {
        orderValue(cJSON["orderValue"].toInt());
    }
}


/**
 * means to order this map among other maps
 *
 * @return  a value indicating the position of this map among others
 */
int Map::orderValue() const {
    return d->m_nOrderValue;
}


/**
 * set the means to order this map among other maps
 *
 * @param   nOrderValue     a value indicating the position of this maps among others
 */
void Map::orderValue(int nOrderValue) {
    if (d->m_nOrderValue == nOrderValue) {
        return;
    }
    d->m_nOrderValue = nOrderValue;
    changed(true);
}


/**
 * save the map to json
 *
 * @param   cJSON       the json instance to save to
 */
void Map::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["orderValue"] = orderValue();
}

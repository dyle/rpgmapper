/*
 * layer.cpp
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

#include <QJsonObject>

// rpgmapper
#include <rpgmapper/layer.hpp>
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {


/**
 * Internal data of a Layer object.
 */
class Layer::Layer_data {

public:

    Layer_data() = default;

    Map * m_cMap = nullptr;             /**< Parent Map back pointer. */
    QString m_sName;                    /**< Layer name. */
};


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cMap        parent object
 * @param   nId         id of the layer
 */
Layer::Layer(Map * cMap, layerid_t nId) : Nameable(cMap), m_nId(nId) {
    Q_ASSERT(cMap);
    d = std::make_shared<Layer::Layer_data>();
    d->m_cMap = cMap;
}


/**
 * Reset the layer to an empty state.
 */
void Layer::clear() {
    name("");
}


/**
 * Create a new layer (factory method) for a map.
 *
 * @param   cMap        parent object
 * @param   nId         the id of the new map layer
 * @return  a new layer
 */
LayerPointer Layer::create(Map * cMap, layerid_t nId) {
    return LayerPointer(new Layer(cMap, nId), &Layer::deleteLater);
}


/**
 * Load the layer from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Layer::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        m_nId = cJSON["id"].toInt();
    }
}


/**
 * Save the layer to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Layer::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
}

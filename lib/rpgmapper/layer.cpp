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

#include <QJsonArray>
#include <QJsonObject>

// rpgmapper
#include <rpgmapper/common_macros.h>
#include <rpgmapper/layer.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/field.hpp>

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

    mutable Fields m_cFields;               /**< All the fields on this on this layer. */
    bool m_bVisible = true;                 /**< Visibility flag. */
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
 * @param   eLayer      the layer type
 */
Layer::Layer(Map * cMap, layerid_t nId, layer_t eLayer) : Nameable{cMap}, m_nId{nId}, m_eLayer{eLayer} {

    Q_ASSERT(cMap);

    d = std::make_shared<Layer::Layer_data>();

    static Tile const cDefaultBackground{{"color", "#000060"}};
    static Tile const cDefaultGrid{{"color", "#f0f0ff"}};

    if (eLayer == layer_t::background) {
        addTile(0,  cDefaultBackground);
    }
    if (eLayer == layer_t::grid) {
        addTile(0, cDefaultGrid);
    }
}


/**
 * Adds a tile to a field on the layer.
 *
 * @param   nCoordinate     the coordinate of the field
 * @param   cTile           the tile to add to the field
 */
void Layer::addTile(coordinate_t nCoordinate, Tile const & cTile) {

    if (!stackable()) {
        clearField(nCoordinate);
    }
    d->m_cFields[nCoordinate].cPosition = Field::position(nCoordinate);
    d->m_cFields[nCoordinate].cTiles.push_back(cTile);
    setModified(true);
}


/**
 * Reset the layer to an empty state.
 */
void Layer::clear() {
    name("");
}


/**
 * Clears and empties a field.
 *
 * @param   nCoordinate     the coordinate of the field
 */
void Layer::clearField(coordinate_t nCoordinate) {
    d->m_cFields[nCoordinate].cTiles.clear();
    setModified(true);
}


/**
 * Create a new layer (factory method) for a map.
 *
 * @param   cMap        parent object
 * @param   nId         the id of the new map layer
 * @param   eLayer      the layer type
 * @return  a new layer
 */
LayerPointer Layer::create(Map * cMap, layerid_t nId, layer_t eLayer) {
    return LayerPointer{new Layer{cMap, nId, eLayer}, &Layer::deleteLater};
}


/**
 * Get one field on this layer.
 *
 * @param   nCoordinate         the field's coordinate value
 * @return  the field requested
 */
Field const & Layer::getField(coordinate_t nCoordinate) const {
    return d->m_cFields[nCoordinate];
}


/**
 * Get all the map items of this layer.
 *
 * @return  all tiles on this layer
 */
Fields const & Layer::fields() const {
    return d->m_cFields;
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
    if (cJSON.contains("type") && cJSON["type"].isDouble()) {
        m_eLayer = static_cast<Layer::layer_t>(cJSON["type"].toInt());
    }
    if (cJSON.contains("visible") && cJSON["visible"].isBool()) {
        d->m_bVisible = cJSON["visible"].toBool();
    }

    if (cJSON.contains("fields")&& cJSON["fields"].isArray()) {
        auto cJSONFields = cJSON["fields"].toArray();
        for (auto && cJSONField : cJSONFields) {
            auto cField = loadFromJson(cJSONField.toObject());
            for (auto const & cTile : cField.cTiles) {
                addTile(cField.cPosition, cTile);
            }
        }
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
    cJSON["type"] = static_cast<int>(type());
    cJSON["visible"] = visible();

    QJsonArray cJSONFields;
    for (auto const & cPair : fields()) {

        if (!cPair.second.isEmpty()) {
            cJSONFields.append(saveToJson(cPair.second));
        }
    }
    cJSON["fields"] = cJSONFields;
}


/**
 * Checks if the tiles on this layer are stackable.
 *
 * Stackable tiles can be piled up on the very same field.
 * If the tiles are not stackable, then there can be only
 * one tile per field.
 *
 * @return  true, if there can be multiple tiles per field
 */
bool Layer::stackable() const {

    bool res;
    switch (type()) {

        case layer_t::background:
        case layer_t::grid:
            res = false;
            break;

        default:
            res = true;
            break;
    }

    return res;
}


/**
 * Checks if this layer is visible.
 *
 * @return  visibility flag
 */
bool Layer::visible() const {
    return d->m_bVisible;
}


/**
 * Switches visibility of this layer.
 *
 * @param   bVisible        new visibility flag
 */
void Layer::visible(bool bVisible) {
    if (d->m_bVisible == bVisible) {
        return;
    }
    d->m_bVisible = bVisible;
    setModified(true);
}

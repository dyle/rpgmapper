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
#include <rpgmapper/layer.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/tile.hpp>

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

    Fields m_cFields;                       /**< All the fields on this on this layer. */
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
    if (eLayer == layer_t::background) {
        addTile(Tile{QPoint{0, 0}, {{"color", QString{"#000060"}}}});
    }
}


/**
 * Adds a tile to the layer.
 *
 * @param   cTile       the tile to add to the layer
 */
void Layer::addTile(Tile cTile) {
    d->m_cFields[Map::convertPointToIndex(cTile.cPosition)].push_back(cTile);
    modified(true);
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
 * @param   eLayer      the layer type
 * @return  a new layer
 */
LayerPointer Layer::create(Map * cMap, layerid_t nId, layer_t eLayer) {
    return LayerPointer{new Layer{cMap, nId, eLayer}, &Layer::deleteLater};
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

    // TODO: load tiles
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

    QJsonArray cJSONTiles;
    for (auto const & cPair : fields()) {
        for (auto const & cField : cPair.second) {
            cJSONTiles.append(saveToJson(cField));
        }
    }
    cJSON["tiles"] = cJSONTiles;
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

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/layer.hpp>
#include "layer_impl.hpp"


Layer::Layer(Map * map, QObject * parent) : QObject{parent} {
    impl = std::make_shared<Layer::Impl>(map);
}


Layer::Attributes & Layer::getAttributes() {
    return impl->getAttributes();
}


Layer::Attributes const & Layer::getAttributes() const {
    return impl->getAttributes();
}







#if 0


#include <QFont>
#include <QJsonArray>
#include <QJsonObject>

// rpgmapper
#include <rpgmapper/layer.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/field.hpp>
#include "layer/backgroundlayer.hpp"
#include "layer/gridlayer.hpp"

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

    Map * m_cMap = nullptr;                     /**< The map this layer belongs to. */
    mutable Fields m_cFields;                   /**< All the fields on this on this layer. */
    std::map<QString, QString> m_cAttributes;   /**< Attributes of this layer. */
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

    if (cMap == nullptr) {
        throw std::invalid_argument("Map shall not be nullptr.");
    }

    d = std::make_shared<Layer::Layer_data>();
    d->m_cMap = cMap;
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
 * Get the attributes of this layer.
 *
 * @return  the attributes of this layer.
 */
std::map<QString, QString> & Layer::attributes() {
    return d->m_cAttributes;
}


/**
 * Get the attributes of this layer.
 *
 * @return  the attributes of this layer.
 */
std::map<QString, QString> const & Layer::attributes() const {
    return d->m_cAttributes;
}


/**
 * Reset the layer to an empty state.
 */
void Layer::clear() {
    setName("");
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

    switch (eLayer) {

        case layer_t::background:
            return LayerPointer{new BackgroundLayer{cMap, nId}, &BackgroundLayer::deleteLater};

        case layer_t::grid:
            return LayerPointer{new GridLayer{cMap, nId}, &GridLayer::deleteLater};

        case layer_t::tile:
        case layer_t::text:
            throw std::runtime_error("Layer enumeration not yet implemented.");
    }

    return LayerPointer{nullptr};
}


/**
 * Draw the current layer given the painter.
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void Layer::draw(QPainter & cPainter, int nTileSize) const {
    drawLayer(cPainter, nTileSize);
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

    if (cJSON.contains("fields") && cJSON["fields"].isArray()) {
        auto cJSONFields = cJSON["fields"].toArray();
        for (auto && cJSONField : cJSONFields) {
            auto cField = loadFromJson(cJSONField.toObject());
            for (auto const & cTile : cField.cTiles) {
                addTile(cField.cPosition, cTile);
            }
        }
    }

    if (cJSON.contains("attributes") && cJSON["attributes"].isObject()) {
        auto cJSONAttributes = cJSON["attributes"].toObject();
        for (auto iter = cJSONAttributes.begin(); iter != cJSONAttributes.end(); ++iter) {
            d->m_cAttributes[iter.key()] = iter.value().toString();
        }
    }

    QJsonObject cJSONAttributes;
    for (auto const & cPair : attributes()) {
        cJSONAttributes[cPair.first] = cPair.second;
    }
    cJSON["attributes"] = cJSONAttributes;

}


/**
 * The map associated with this layer.
 *
 * @return  a pointer to the map
 */
Map * const & Layer::map() const {
    return d->m_cMap;
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

    QJsonArray cJSONFields;
    for (auto const & cPair : fields()) {

        if (!cPair.second.isEmpty()) {
            cJSONFields.append(saveToJson(cPair.second));
        }
    }
    cJSON["fields"] = cJSONFields;
    
    QJsonObject cJSONAttributes;
    for (auto const & cPair : attributes()) {
        cJSONAttributes[cPair.first] = cPair.second;
    }
    cJSON["attributes"] = cJSONAttributes;
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


#endif

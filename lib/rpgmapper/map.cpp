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
// defs

#define MAP_HEIGHT_DEFAULT          10
#define MAP_WIDTH_DEFAULT           10


// ------------------------------------------------------------
// incs

#include <cassert>

#include <QJsonArray>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/layer.hpp>

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

    Atlas * m_cAtlas = nullptr;                                     /**< Parent atlas back pointer. */
    Layers m_cLayers;                                               /**< The layers of this map. */
    int m_nOrderValue = 0;                                          /**< Means to order a map among others. */
    regionid_t m_nRegionId = -1;                                    /**< Id of the region of this map. */
    QSize m_cSize{MAP_WIDTH_DEFAULT, MAP_HEIGHT_DEFAULT};           /**< Size of the map. */
};


/**
 * Global map id counter.
 */
static mapid_t g_nMapIdCounter = 0;


}
}


/**
 * Load a size from a JSON object.
 *
 * @param   cJSON       the JSON object
 * @param   cSize       the size extracted
 * @return  true, if a size node has been found
 */
bool loadSize(QJsonObject const  & cJSON, QSize & cSize);


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cAtlas      parent object
 * @param   nId     id of the map
 */
Map::Map(Atlas * cAtlas, mapid_t nId) : Nameable{cAtlas}, m_nId{nId} {

    assert(cAtlas != nullptr);

    d = std::make_shared<Map::Map_data>();
    d->m_cAtlas = cAtlas;
    d->m_nOrderValue = nId;

    init();
}


/**
 * Reset the map to an empty state.
 */
void Map::clear() {
    d->m_cLayers.clear();
    createDefaultLayers();
    setName("");
}


/**
 * Create a new map (factory method).
 *
 * @param   cAtlas      parent object
 * @return  a new map
 */
MapPointer Map::create(Atlas * cAtlas) {
    return MapPointer{new Map{cAtlas, ++g_nMapIdCounter}, &Map::deleteLater};
}


/**
 * Adds the standard default layers to the map.
 */
void Map::createDefaultLayers() {

    struct LayerDefinition {
        layerid_t nId;
        Layer::layer_t eLayer;
        QString sName;
    };

    std::vector<LayerDefinition> cDefaultLayers {
        { static_cast<layerid_t>(map_layer::background), Layer::layer_t::background, "Background"},
        { static_cast<layerid_t>(map_layer::base), Layer::layer_t::tile, "Base"},
        { static_cast<layerid_t>(map_layer::walls), Layer::layer_t::tile, "Walls"},
        { static_cast<layerid_t>(map_layer::grid), Layer::layer_t::grid, "Grid"},
        { static_cast<layerid_t>(map_layer::specials), Layer::layer_t::tile, "Specials"},
        { static_cast<layerid_t>(map_layer::text), Layer::layer_t::text, "Text"},
    };

    for (auto const & cLayerDefinition : cDefaultLayers) {
        d->m_cLayers[cLayerDefinition.nId] = Layer::create(this,
                                                           cLayerDefinition.nId,
                                                           cLayerDefinition.eLayer);
        d->m_cLayers[cLayerDefinition.nId]->setName(cLayerDefinition.sName);
    }
}


/**
 * Creates a nice initial state.
 */
void Map::init() {
    clear();
    setName("New map " + QString::number(id()));
}


/**
 * Get a certain layer of this map.
 *
 * @param   eLayer      the layer requested
 * @return  the layers of this map
 */
LayerPointer const & Map::layer(map_layer eLayer) const {
    return d->m_cLayers[static_cast<layerid_t>(eLayer)];
}


/**
 * Get the layers of this map.
 *
 * @return  the layers of this map
 */
Layers const & Map::layers() const {
    return d->m_cLayers;
}


/**
 * Load the map from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Map::load(QJsonObject const & cJSON) {

    clear();
    Nameable::load(cJSON);

    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        m_nId = cJSON["id"].toInt();
        g_nMapIdCounter = std::max(g_nMapIdCounter, m_nId);
    }

    if (cJSON.contains("setOrderValue") && cJSON["setOrderValue"].isDouble()) {
        setOrderValue(cJSON["setOrderValue"].toInt());
    }

    QSize cSize{0, 0};
    if (loadSize(cJSON, cSize)) {
        setSize(cSize);
    }
    
//      TODO
//    QJsonArray cJSONLayers;
//    for (auto const & cLayer: d->m_cLayers) {
//        QJsonObject cJSONLayer;
//        cLayer.second->save(cJSONLayer);
//        cJSONLayers.append(cJSONLayer);
//    }
//    cJSON["layers"] = cJSONLayers;
}


/**
 * Load the map from json.
 *
 * @param   cJSON       the json instance to load from
 * @param   cAtlas      parent object
 * @return  the loaded map instance
 */
MapPointer Map::load(QJsonObject const & cJSON, Atlas * cAtlas) {
    auto cMap = MapPointer{new Map{cAtlas, -1}, &Map::deleteLater};
    cMap->load(cJSON);
    return cMap;
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
 * Return the region to which this map belongs to.
 *
 * @return  the region of this map
 */
RegionPointer const Map::region() const {
    return d->m_cAtlas->regionById(d->m_nRegionId);
}


/**
 * Set the means to order this map among other maps.
 *
 * @param   nOrderValue     a value indicating the position of this maps among others
 */
void Map::setOrderValue(int nOrderValue) {

    if (d->m_nOrderValue == nOrderValue) {
        return;
    }

    d->m_nOrderValue = nOrderValue;
    setModified(true);
    emit changedOrderValue();
}


/**
 * Set the region this map belongs.
 *
 * @param   cRegion     the new region of this map
 */
void Map::setRegion(RegionPointer cRegion) {

    if (cRegion.data() == nullptr) {
        return;
    }

    auto nRegionId = cRegion->id();
    if (d->m_nRegionId == nRegionId) {
        return;
    }

    d->m_nRegionId = cRegion->id();
    emit changedRegion();
}


/**
 * Sets a new size of the map.
 *
 * @param   cSize       the new size of the map
 */
void Map::setSize(QSize cSize) {

    if (d->m_cSize == cSize) {
        return;
    }

    if (cSize.width() < MINIMUM_MAP_WIDTH) {
        throw std::out_of_range("Map width may not be below " + std::to_string(MINIMUM_MAP_WIDTH) + ".");
    }
    if (cSize.height() < MINIMUM_MAP_HEIGHT) {
        throw std::out_of_range("Map height may not be below " + std::to_string(MINIMUM_MAP_HEIGHT) + ".");
    }
    if (cSize.width() > MAXIMUM_MAP_WIDTH) {
        throw std::out_of_range("Map width may not be above " + std::to_string(MAXIMUM_MAP_WIDTH) + ".");
    }
    if (cSize.height() > MAXIMUM_MAP_HEIGHT) {
        throw std::out_of_range("Map height may not be above " + std::to_string(MAXIMUM_MAP_HEIGHT) + ".");
    }

    d->m_cSize = cSize;
    emit changedSize();
}


/**
 * Save the map to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Map::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["region"] = d->m_nRegionId;
    cJSON["setOrderValue"] = orderValue();

    QJsonObject cJSONSize;
    cJSONSize["width"] = size().width();
    cJSONSize["height"] = size().height();
    cJSON["size"] = cJSONSize;

    QJsonArray cJSONLayers;
    for (auto const & cLayer: layers()) {
        QJsonObject cJSONLayer;
        cLayer.second->save(cJSONLayer);
        cJSONLayers.append(cJSONLayer);
    }
    cJSON["layers"] = cJSONLayers;
}


/**
 * Returns the size of the map.
 *
 * @return  the size of the map
 */
QSize Map::size() const {
    return d->m_cSize;
}


/**
 * Load a size from a JSON object.
 *
 * @param   cJSON       the JSON object
 * @param   cSize       the size extracted
 * @return  true, if a size node has been found
 */
bool loadSize(QJsonObject const  & cJSON, QSize & cSize) {

    if (cJSON.contains("size") && cJSON["size"].isObject()) {

        auto cJSONSize = cJSON["size"].toObject();

        if (cJSONSize.contains("width") && cJSONSize["width"].isDouble()) {
            cSize.setWidth(cJSONSize["width"].toInt());
        }
        if (cJSONSize.contains("height") && cJSONSize["height"].isDouble()) {
            cSize.setHeight(cJSONSize["height"].toInt());
        }

        return true;
    }

    return false;
}

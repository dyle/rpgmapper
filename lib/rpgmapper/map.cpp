/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Map(QString const & name, Region * region) : QObject{region} {
    impl = std::make_shared<Map::Impl>(this, region);
    impl->setName(name);
}


bool Map::applyJsonObject(QJsonObject const & json) {
    return impl->applyJsonObject(json);
}


LayerPointer const & Map::getBackgroundLayer() const {
    return impl->getBackgroundLayer();
}

Layers const & Map::getBaseLayers() const {
    return impl->getBaseLayers();
}

LayerPointer const & Map::getGridLayer() const {
    return impl->getGridLayer();
}


QJsonObject Map::getJsonObject() const {
    return impl->getJsonObject();
}


QString const & Map::getName() const {
    return impl->getName();
}


Region * Map::getRegion() {
    return impl->getRegion();
}


LayerPointer const & Map::getTextLayer() const {
    return impl->getTextLayer();
}


Layers const & Map::getTileLayers() const {
    return impl->getTileLayers();
}


void Map::setName(QString const & name) {
    if (name == impl->getName()) {
        return;
    }
    impl->setName(name);
    emit changedName();
}

















#if 0


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
    map_corner m_eCorner = map_corner::bottomLeft;                  /**< Orgin corner of the map. */
    QPoint m_cOriginOffset;                                         /**< Origin coordinate offset. */
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
 * Load an orgin offset from a JSON object.
 *
 * @param   cJSON       the JSON object
 * @param   cOffset     the origin offset extracted
 * @return  true, if an offset node has been found
 */
bool loadOriginOffset(QJsonObject const  & cJSON, QPoint & cOffset);


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

    if (cAtlas == nullptr) {
        throw std::invalid_argument("Atlas argument shall not be nullptr.");
    }

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
    if (cAtlas == nullptr) {
        throw std::invalid_argument("Atlas argument shall not be nullptr.");
    }
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

        // TODO
        // { static_cast<layerid_t>(map_layer::base), Layer::layer_t::tile, "Base"},
        // { static_cast<layerid_t>(map_layer::walls), Layer::layer_t::tile, "Walls"},
        { static_cast<layerid_t>(map_layer::grid), Layer::layer_t::grid, "Grid"},
        // { static_cast<layerid_t>(map_layer::specials), Layer::layer_t::tile, "Specials"},
        // { static_cast<layerid_t>(map_layer::text), Layer::layer_t::text, "Text"},
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
LayerPointer & Map::layer(map_layer eLayer) {
    return d->m_cLayers[static_cast<layerid_t>(eLayer)];
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

    if (cJSON.contains("corner") && cJSON["corner"].isString()) {
        auto sCorner = cJSON["corner"].toString();
        if (sCorner == "bottomLeft") {
            setOriginCorner(Map::map_corner::bottomLeft);
        }
        else if (sCorner == "bottomRight") {
            setOriginCorner(Map::map_corner::bottomRight);
        }
        else if (sCorner == "topLeft") {
            setOriginCorner(Map::map_corner::topLeft);
        }
        else if (sCorner == "topRight") {
            setOriginCorner(Map::map_corner::topRight);
        }
    }

    QPoint cOriginOffset{0, 0};
    if (loadOriginOffset(cJSON, cOriginOffset)) {
        setOriginOffset(cOriginOffset);
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
 * Get the corner of the map's origin.
 *
 * @return  the corner for (0, 0)
 */
Map::map_corner Map::originCorner() const {
    return d->m_eCorner;
}


/**
 * The offest of the origin coordinate.
 *
 * Map coordinates are relative to this offset value.
 *
 * @return  the offset of the origin coordinate on this map
 */
QPoint const & Map::originOffset() const {
    return d->m_cOriginOffset;
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
 * Save the map to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Map::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["region"] = d->m_nRegionId;
    cJSON["setOrderValue"] = orderValue();

    QJsonObject cJSONOffset;
    cJSONOffset["x"] = originOffset().x();
    cJSONOffset["y"] = originOffset().y();
    cJSON["originOffset"] = cJSONOffset;

    QJsonObject cJSONSize;
    cJSONSize["width"] = size().width();
    cJSONSize["height"] = size().height();
    cJSON["size"] = cJSONSize;

    switch (originCorner()) {
        case Map::map_corner::bottomLeft:
            cJSON["corner"] = "bottomLeft";
            break;
        case Map::map_corner::bottomRight:
            cJSON["corner"] = "bottomRight";
            break;
        case Map::map_corner::topLeft:
            cJSON["corner"] = "topLeft";
            break;
        case Map::map_corner::topRight:
            cJSON["corner"] = "topRight";
            break;
    }

    QJsonArray cJSONLayers;
    for (auto const & cLayer: layers()) {
        QJsonObject cJSONLayer;
        cLayer.second->save(cJSONLayer);
        cJSONLayers.append(cJSONLayer);
    }
    cJSON["layers"] = cJSONLayers;
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
 * Set the corner of the map's origin.
 *
 * @param   eCorner         the new map's corner of origin
 */
void Map::setOriginCorner(Map::map_corner eCorner) {
    if (d->m_eCorner == eCorner) {
        return;
    }
    d->m_eCorner = eCorner;
    emit changedOriginCorner();
}


/**
 * Adjust the offest of the origin coordinate.
 *
 * @param   cOffset         offset of the origin
 */
void Map::setOriginOffset(QPoint cOffset) {
    if (d->m_cOriginOffset == cOffset) {
        return;
    }
    d->m_cOriginOffset = cOffset;
    emit changedOriginOffset();
}


/**
 * Set the region this map belongs.
 *
 * @param   cRegion     the new region of this map
 */
void Map::setRegion(RegionPointer & cRegion) {

    if (cRegion.data() == nullptr) {
        return;
    }

    auto nRegionId = cRegion->id();
    if (d->m_nRegionId == nRegionId) {
        return;
    }

    auto cOldRegion = d->m_cAtlas->regionById(d->m_nRegionId);
    if (cOldRegion.data() != nullptr) {
        cOldRegion->removedMap(id());
    }

    d->m_nRegionId = cRegion->id();
    cRegion->addMap(d->m_cAtlas->mapById(id()));

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
 * Returns the size of the map.
 *
 * @return  the size of the map
 */
QSize Map::size() const {
    return d->m_cSize;
}


/**
 * Turn map coordinates into user coordinates.
 *
 * @param   cPoint          the map coordinate
 * @return  the user coordinates
 */
Map::UserCoordinates Map::translate(QPoint const & cPoint) const {

    Map::UserCoordinates cUserCoordinates;

    if (QRect{QPoint{0, 0}, size()}.contains(cPoint, false)) {
        cUserCoordinates.m_sX = translateX(cPoint.x());
        cUserCoordinates.m_sY = translateY(cPoint.y());
    }

    return cUserCoordinates;
}


/**
 * Translate the X coordinate to the user value.
 *
 * @param   x       x on the map
 * @return  value shown to the user
 */
QString Map::translateX(int x) const {
    // TODO: respect corner
    if ((x < 0) || (x >= size().width())) {
        return "";
    }
    return QString::number(x + originOffset().x());
}


/**
 * Translate the Y coordinate to the user value.
 *
 * @param   y       y on the map
 * @return  value shown to the user
 */
QString Map::translateY(int y) const {
    // TODO: respect corner
    if ((y < 0) || (y >= size().height())) {
        return "";
    }
    return QString::number(y + originOffset().y());
}


/**
 * Load an orgin offset from a JSON object.
 *
 * @param   cJSON       the JSON object
 * @param   cOffset     the origin offset extracted
 * @return  true, if an offset node has been found
 */
bool loadOriginOffset(QJsonObject const  & cJSON, QPoint & cOffset) {

    if (cJSON.contains("originOffset") && cJSON["originOffset"].isObject()) {

        auto cJSONOffset = cJSON["originOffset"].toObject();

        if (cJSONOffset.contains("x") && cJSONOffset["x"].isDouble()) {
            cOffset.setX(cJSONOffset["x"].toInt());
        }
        if (cJSONOffset.contains("y") && cJSONOffset["y"].isDouble()) {
            cOffset.setY(cJSONOffset["y"].toInt());
        }

        return true;
    }

    return false;
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


#endif

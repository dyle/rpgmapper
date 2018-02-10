/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include "layer/background_layer.hpp"
#include "layer/base_layer.hpp"
#include "layer/grid_layer.hpp"
#include "layer/text_layer.hpp"
#include "layer/tile_layer.hpp"
#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Impl::Impl(Map * map, Region * region) : map{map}, region{region} {
    if (map == nullptr) {
        throw std::invalid_argument{"Map must not be nullptr."};
    }
    backgroundLayer = LayerPointer{new BackgroundLayer{map}};
    baseLayers = Layers{LayerPointer{new BaseLayer{map}}};
    gridLayer = LayerPointer{new GridLayer{map}};
    textLayer = LayerPointer{new TextLayer{map}};
    tileLayers = Layers{LayerPointer{new TileLayer{map}}};
}


bool Map::Impl::applyJsonObject(QJsonObject const & json) {
    auto result = Nameable::applyJsonObject(json);
    return result;
}


LayerPointer const & Map::Impl::getBackgroundLayer() const {
    return backgroundLayer;
}

Layers const & Map::Impl::getBaseLayers() const {
    return baseLayers;
}

LayerPointer const & Map::Impl::getGridLayer() const {
    return gridLayer;
}


QJsonObject Map::Impl::getJsonObject() const {
    auto json = Nameable::getJsonObject();
    return json;
}


Layers const & Map::Impl::getTileLayers() const {
    return tileLayers;
}

LayerPointer const & Map::Impl::getTextLayer() const {
    return textLayer;
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/background_layer.hpp>
#include <rpgmapper/layer/grid_layer.hpp>
#include <rpgmapper/layer/text_layer.hpp>
#include <rpgmapper/layer/tile_layer.hpp>
#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Impl::Impl(Map * map, Region * region) : map{map}, region{region} {
    if (map == nullptr) {
        throw std::invalid_argument{"Map must not be nullptr."};
    }
    backgroundLayer = BackgroundLayerPointer{new BackgroundLayer{map}};
    baseLayers = TileLayers{TileLayerPointer{new TileLayer{map}}};
    gridLayer = GridLayerPointer{new GridLayer{map}};
    textLayer = TextLayerPointer{new TextLayer{map}};
    tileLayers = TileLayers{TileLayerPointer{new TileLayer{map}}};
}


bool Map::Impl::applyJsonObject(QJsonObject const & json) {
    auto result = Nameable::applyJsonObject(json);
    return result;
}


QJsonObject Map::Impl::getJsonObject() const {
    auto json = Nameable::getJsonObject();
    return json;
}

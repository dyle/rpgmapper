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

static QSize const MAP_SIZE_DEFAULT{10, 10};


Map::Impl::Impl(Map * map, Region * region) : map{map}, region{region}, size{MAP_SIZE_DEFAULT} {
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


QJsonObject Map::Impl::getJsonObject() const {
    auto json = Nameable::getJsonObject();
    return json;
}


void Map::Impl::resize(QSize const & size) {
    if ((size.width() < Map::getSizeMinimum().width()) || (size.height() < Map::getSizeMinimum().height())) {
        return;
    }
    if ((size.width() > Map::getSizeMaximum().width()) || (size.height() > Map::getSizeMaximum().height())) {
        return;
    }
    this->size = size;
}

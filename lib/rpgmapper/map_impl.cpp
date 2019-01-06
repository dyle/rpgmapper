/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <QJsonArray>

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

    axisLayer = AxisLayerPointer{new AxisLayer{map}};
    backgroundLayer = BackgroundLayerPointer{new BackgroundLayer{map}};
    baseLayers = TileLayers{TileLayerPointer{new TileLayer{map}}};
    gridLayer = GridLayerPointer{new GridLayer{map}};
    textLayer = TextLayerPointer{new TextLayer{map}};
    tileLayers = TileLayers{TileLayerPointer{new TileLayer{map}}};
}


bool Map::Impl::applyJsonBaseLayers(QJsonArray const & jsonArray) {

    bool applied = true;
    baseLayers.clear();
    for (auto && json : jsonArray) {
        auto baseLayer = TileLayerPointer{new TileLayer{map}};
        applied = applied && baseLayer->applyJSON(json.toObject());
        baseLayers.push_back(baseLayer);
    }

    return applied;
}


bool Map::Impl::applyJsonLayers(QJsonObject const & json) {

    bool applied = true;

    if (applied && json.contains("axis") && json["axis"].isObject()) {
        applied = getAxisLayer()->applyJSON(json["axis"].toObject());
    }
    if (applied && json.contains("background") && json["background"].isObject()) {
        applied = getBackgroundLayer()->applyJSON(json["background"].toObject());
    }
    if (applied && json.contains("base") && json["base"].isArray()) {
        applied = applyJsonBaseLayers(json["base"].toArray());
    }
    if (applied && json.contains("grid") && json["grid"].isObject()) {
        applied = getGridLayer()->applyJSON(json["grid"].toObject());
    }
    if (applied && json.contains("tile") && json["tile"].isArray()) {
        applied = applyJsonTileLayers(json["tile"].toArray());
    }
    if (applied && json.contains("text") && json["text"].isObject()) {
        applied = getTextLayer()->applyJSON(json["text"].toObject());
    }

    return applied;
}


bool Map::Impl::applyJSON(QJsonObject const & json) {

    if (!Nameable::applyJSON(json)) {
        return false;
    }
    if (json.contains("coordinateSystem") && json["coordinateSystem"].isObject()) {
        if (!CoordinateSystem::applyJSON(json["coordinateSystem"].toObject())) {
            return false;
        }
    }

    if (json.contains("layers") && json["layers"].isObject()) {
        return applyJsonLayers(json["layers"].toObject());
    }

    return true;
}


bool Map::Impl::applyJsonTileLayers(QJsonArray const & jsonArray) {

    bool applied = true;
    tileLayers.clear();
    for (auto && json : jsonArray) {
        auto tileLayer = TileLayerPointer{new TileLayer{map}};
        applied = applied && tileLayer->applyJSON(json.toObject());
        tileLayers.push_back(tileLayer);
    }
    return applied;
}




QJsonObject Map::Impl::getJSON(rpgmapper::model::io::Content & content) const {

    auto json = Nameable::getJSON(content);
    json["coordinateSystem"] = CoordinateSystem::getJSON(content);

    QJsonObject layers;
    layers["axis"] = getAxisLayer()->getJSON(content);
    layers["background"] = getBackgroundLayer()->getJSON(content);

    QJsonArray jsonBaseLayers;
    for (auto const & baseLayer: baseLayers) {
        jsonBaseLayers.append(baseLayer->getJSON(content));
    }
    layers["base"] = jsonBaseLayers;

    layers["grid"] = getGridLayer()->getJSON(content);
    QJsonArray jsonTileLayers;
    for (auto const & tileLayer: tileLayers) {
        jsonTileLayers.append(tileLayer->getJSON(content));
    }
    layers["tile"] = jsonTileLayers;

    layers["text"] = getTextLayer()->getJSON(content);

    json["layers"] = layers;

    return json;
}


QString const & Map::Impl::getRegionName() const {
    static QString nullName = QString::null;
    return region != nullptr ? region->getName() : nullName;
}



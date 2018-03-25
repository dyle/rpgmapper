/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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
        applied = applied && baseLayer->applyJsonObject(json.toObject());
        baseLayers.push_back(baseLayer);
    }

    return applied;
}


bool Map::Impl::applyJsonLayers(QJsonObject const & json) {

    bool applied = true;

    if (applied && json.contains("axis") && json["axis"].isObject()) {
        applied = getAxisLayer()->applyJsonObject(json["axis"].toObject());
    }
    if (applied && json.contains("background") && json["background"].isObject()) {
        applied = getBackgroundLayer()->applyJsonObject(json["background"].toObject());
    }
    if (applied && json.contains("base") && json["base"].isArray()) {
        applied = applyJsonBaseLayers(json["base"].toArray());
    }
    if (applied && json.contains("grid") && json["grid"].isObject()) {
        applied = getGridLayer()->applyJsonObject(json["grid"].toObject());
    }
    if (applied && json.contains("tile") && json["tile"].isArray()) {
        applied = applyJsonTileLayers(json["tile"].toArray());
    }
    if (applied && json.contains("text") && json["text"].isObject()) {
        applied = getTextLayer()->applyJsonObject(json["text"].toObject());
    }

    return applied;
}


bool Map::Impl::applyJsonObject(QJsonObject const & json) {

    if (!Nameable::applyJsonObject(json)) {
        return false;
    }
    if (json.contains("coordinateSystem") && json["coordinateSystem"].isObject()) {
        if (!CoordinateSystem::applyJsonObject(json["coordinateSystem"].toObject())) {
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
        applied = applied && tileLayer->applyJsonObject(json.toObject());
        tileLayers.push_back(tileLayer);
    }
    return applied;
}


QString Map::Impl::getInvalidCharactersInName() {
    return R"raw(:\\*\?/)raw";
}


QJsonObject Map::Impl::getJsonObject(rpgmapper::model::io::Content & content) const {

    auto json = Nameable::getJsonObject(content);
    json["coordinateSystem"] = CoordinateSystem::getJsonObject(content);

    QJsonObject layers;
    layers["axis"] = getAxisLayer()->getJsonObject(content);
    layers["background"] = getBackgroundLayer()->getJsonObject(content);

    QJsonArray jsonBaseLayers;
    for (auto const & baseLayer: baseLayers) {
        jsonBaseLayers.append(baseLayer->getJsonObject(content));
    }
    layers["base"] = jsonBaseLayers;

    layers["grid"] = getGridLayer()->getJsonObject(content);
    QJsonArray jsonTileLayers;
    for (auto const & tileLayer: tileLayers) {
        jsonTileLayers.append(tileLayer->getJsonObject(content));
    }
    layers["tile"] = jsonTileLayers;

    layers["text"] = getTextLayer()->getJsonObject(content);

    json["layers"] = layers;

    return json;
}


QString const & Map::Impl::getRegionName() const {
    static QString nullName = QString::null;
    return region != nullptr ? region->getName() : nullName;
}


bool Map::Impl::isNameValid(QString name) {
    QRegExp regExp{QString{"[%1]"}.arg(getInvalidCharactersInName())};
    return (!name.isEmpty()) && (regExp.indexIn(name) == -1);
}

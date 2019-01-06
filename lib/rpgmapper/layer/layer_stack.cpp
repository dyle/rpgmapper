/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/layer_stack.hpp>

using namespace rpgmapper::model::layer;


LayerStack::LayerStack(Map * map) : map{nullptr} {
    
    axisLayer = QSharedPointer<AxisLayer>{new AxisLayer{map}};
    backgroundLayer = QSharedPointer<BackgroundLayer>{new BackgroundLayer{map}};
    baseLayers.push_back(QSharedPointer<TileLayer>{new TileLayer{map}});
    gridLayer = QSharedPointer<GridLayer>{new GridLayer{map}};
    tileLayers.push_back(QSharedPointer<TileLayer>{new TileLayer{map}});
    textLayer = QSharedPointer<TextLayer>{new TextLayer{map}};
    
    currentBaseLayer = 0;
    currentTileLayer = 0;
    
    setMap(map);
}


bool LayerStack::applyJSON(QJsonObject const & json) {
    
    bool applied = true;
    
    if (json.contains("background") && json["background"].isObject()) {
        applied = getBackgroundLayer()->applyJSON(json["background"].toObject());
    }
    if (applied && json.contains("base") && json["base"].isArray()) {
        applied = applyJSONBaseLayers(json["base"].toArray());
    }
    if (applied && json.contains("grid") && json["grid"].isObject()) {
        applied = getGridLayer()->applyJSON(json["grid"].toObject());
    }
    if (applied && json.contains("axis") && json["axis"].isObject()) {
        applied = getAxisLayer()->applyJSON(json["axis"].toObject());
    }
    if (applied && json.contains("tile") && json["tile"].isArray()) {
        applied = applyJSONTileLayers(json["tile"].toArray());
    }
    if (applied && json.contains("text") && json["text"].isObject()) {
        applied = getTextLayer()->applyJSON(json["text"].toObject());
    }
    
    return applied;
}


bool LayerStack::applyJSONBaseLayers(QJsonArray const & jsonArray) {
    
    bool applied = true;
    baseLayers.clear();
    for (auto && json : jsonArray) {
        auto baseLayer = QSharedPointer<TileLayer>{new TileLayer{getMap()}};
        applied = applied && baseLayer->applyJSON(json.toObject());
        baseLayers.push_back(baseLayer);
    }
    
    return applied;
}


bool LayerStack::applyJSONTileLayers(QJsonArray const & jsonArray) {
    
    bool applied = true;
    tileLayers.clear();
    for (auto && json : jsonArray) {
        auto baseLayer = QSharedPointer<TileLayer>{new TileLayer{getMap()}};
        applied = applied && baseLayer->applyJSON(json.toObject());
        baseLayers.push_back(baseLayer);
    }
    
    return applied;
}


QJsonObject LayerStack::getJSON() const {
    
    QJsonObject json;
    
    json["background"] = getBackgroundLayer()->getJSON();
    
    QJsonArray jsonBaseJson;
    for (auto const & baseLayer: getBaseLayers()) {
        jsonBaseJson.append(baseLayer->getJSON());
    }
    json["base"] = jsonBaseJson;
    json["grid"] = getGridLayer()->getJSON();
    json["axis"] = getAxisLayer()->getJSON();
    
    QJsonArray jsonTileJson;
    for (auto const & tileLayer: getTileLayers()) {
        jsonTileJson.append(tileLayer->getJSON());
    }
    json["tile"] = jsonTileJson;
    json["text"] = getTextLayer()->getJSON();
    
    return json;
}


void LayerStack::setMap(Map * map) {
    
    this->map = map;
    
    axisLayer->setMap(map);
    backgroundLayer->setMap(map);
    for (auto & layer : baseLayers) {
        layer->setMap(map);
    }
    gridLayer->setMap(map);
    for (auto & layer : tileLayers) {
        layer->setMap(map);
    }
    textLayer->setMap(map);
}

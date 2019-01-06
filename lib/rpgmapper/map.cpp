/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/session.hpp>


using namespace rpgmapper::model;
using namespace rpgmapper::model::layer;
using namespace rpgmapper::model::tile;


Map::Map(QString mapName) : Nameable{std::move(mapName)} {
    coordinateSystem = QSharedPointer<CoordinateSystem>(new CoordinateSystem);
    layerStack.setMap(this);
}


bool Map::applyJSON(QJsonObject const & json) {
    
    auto appliedName = Nameable::applyJSON(json);
    
    auto appliedCoordinateSystem = false;
    if (json.contains("coordinate_system") && json["coordinate_system"].isObject()) {
        appliedCoordinateSystem = coordinateSystem->applyJSON(json["coordinate_system"].toObject());
    }
    
    auto appliedLayerStack = false;
    if (json.contains("layers") && json["layers"].isObject()) {
        appliedLayerStack = getLayers().applyJSON(json["layers"].toObject());
    }
    
    return appliedName && appliedLayerStack && appliedCoordinateSystem;
}


QJsonObject Map::getJSON() const {
    auto json = Nameable::getJSON();
    json["coordinate_system"] = coordinateSystem->getJSON();
    json["layers"] = getLayers().getJSON();
    return json;
}


bool Map::isTileOnField(int x, int y) const {
    
    bool tileOnFieldPresent = false;
    
    auto const & baseLayers = getLayers().getBaseLayers();
    auto const & tileLayers = getLayers().getTileLayers();
    
    for (auto iter = baseLayers.begin(); (iter != baseLayers.end()) && !tileOnFieldPresent; ++iter) {
        tileOnFieldPresent = (*iter)->isFieldPresent(x, y);
    }
    for (auto iter = tileLayers.begin(); (iter != tileLayers.end()) && !tileOnFieldPresent; ++iter) {
        tileOnFieldPresent = (*iter)->isFieldPresent(x, y);
    }
    
    return tileOnFieldPresent;
}


MapPointer const & Map::null() {
    static MapPointer nullMap{new InvalidMap};
    return nullMap;
}


void Map::triggerTilePlaced() {
    emit tilePlaced();
}

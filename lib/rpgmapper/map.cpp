/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/session.hpp>
#include <rpgmapper/tile.hpp>


using namespace rpgmapper::model;


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


MapPointer const & Map::null() {
    static MapPointer nullMap{new InvalidMap};
    return nullMap;
}


bool Map::place(float x, float y, rpgmapper::model::TilePointer tile) {
    
    auto size = getCoordinateSystem()->getSize();
    if (!(x >= 0.0f) && (x < size.width()) && (y >= 0.0f) && (y < size.height()) && tile) {
        return false;
    }
    
    auto placed = tile->place(x, y, &layerStack);
    if (placed) {
        auto session = Session::getCurrentSession();
        session->setLastAppliedTile(tile);
    }
    return placed;
}

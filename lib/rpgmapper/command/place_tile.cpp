/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/place_tile.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


PlaceTile::PlaceTile(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position)
        : mapName{std::move(mapName)}, position{position}, tile{std::move(tile)} {
}


void PlaceTile::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    bool placed = false;
    replacedTiles = tile->place(placed, map, position);
}


QString PlaceTile::getDescription() const {
    return QString{"Place tile on map %1 at (%2, %3)"}.arg(mapName).arg(position.x()).arg(position.y());
}


void PlaceTile::undo() {
    throw std::runtime_error{"PlaceTile::undo() called: instantiated a PlaceTile command directly."};
}

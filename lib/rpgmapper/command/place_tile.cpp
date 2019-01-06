/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/place_tile.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/tile/tiles.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;
using namespace rpgmapper::model::tile;


PlaceTile::PlaceTile(rpgmapper::model::Map * map, rpgmapper::model::tile::TilePointer tile, QPointF position)
        : map{map}, position{position}, tile{std::move(tile)} {
}


void PlaceTile::execute() {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    tile = tile->place(replacedTiles, map, position);
    if (tile) {
        map->triggerTilePlaced();
        auto session = Session::getCurrentSession();
        session->setLastAppliedTile(tile);
    }
}


QString PlaceTile::getDescription() const {
    
    QString mapName;
    if (map) {
        mapName = map->getName();
    }
    
    return QString{"Place tile on map %1 at (%2, %3)"}.arg(mapName).arg(position.x()).arg(position.y());
}


void PlaceTile::undo() {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    tile->remove();
    for (auto & replacedTile : replacedTiles) {
        Tiles tiles;
        replacedTile->place(tiles, map, position);
    }
    map->triggerTilePlaced();
}

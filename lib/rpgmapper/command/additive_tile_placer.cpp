/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/additive_tile_placer.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_pointer.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model::command;


AdditiveTilePlacer::AdditiveTilePlacer(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position)
    : PlaceTile{std::move(mapName), std::move(tile), std::move(position)} {
}


void AdditiveTilePlacer::execute() {
    PlaceTile::execute();
}


void AdditiveTilePlacer::undo() {
    
    auto map = Session::getCurrentSession()->findMap(getMapName());
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    getTile()->remove(getMapName(), getPosition());
}

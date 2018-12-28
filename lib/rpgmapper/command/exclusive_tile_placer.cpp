/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/exclusive_tile_placer.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_pointer.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model::command;


ExclusiveTilePlacer::ExclusiveTilePlacer(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position)
    : PlaceTile{std::move(mapName), std::move(tile), std::move(position)} {
}


void ExclusiveTilePlacer::execute() {
    PlaceTile::execute();
}


void ExclusiveTilePlacer::undo() {
    
    auto map = Session::getCurrentSession()->findMap(getMapName());
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
}

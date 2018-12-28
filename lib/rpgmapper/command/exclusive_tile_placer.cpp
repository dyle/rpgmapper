/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/exclusive_tile_placer.hpp>

using namespace rpgmapper::model::command;


ExclusiveTilePlacer::ExclusiveTilePlacer(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position)
    : PlaceTile{std::move(mapName), std::move(tile), std::move(position)} {
}


void ExclusiveTilePlacer::execute() {
    PlaceTile::execute();
}


void ExclusiveTilePlacer::undo() {
    PlaceTile::undo();
}

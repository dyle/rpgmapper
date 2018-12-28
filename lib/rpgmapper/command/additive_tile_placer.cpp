/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/additive_tile_placer.hpp>

using namespace rpgmapper::model::command;


AdditiveTilePlacer::AdditiveTilePlacer(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position)
    : PlaceTile{std::move(mapName), std::move(tile), std::move(position)} {
}


void AdditiveTilePlacer::execute() {
    PlaceTile::execute();
}


void AdditiveTilePlacer::undo() {
    PlaceTile::undo();
}

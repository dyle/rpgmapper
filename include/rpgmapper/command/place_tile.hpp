/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_PLACE_TILE_HPP
#define RPGMAPPER_MODEL_COMMAND_PLACE_TILE_HPP

#include <QPointF>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/tile/tile_pointer.hpp>
#include <rpgmapper/tile/tiles.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper::model::command {


/**
 * This command places a tile on a map.
 */
class PlaceTile : public Command {
    
    rpgmapper::model::Map * map = nullptr;                  /**< The map to place the tile. */
    QPointF position;                                       /**< Position on the map to place the tile. */
    rpgmapper::model::tile::TilePointer tile;               /**< The tile to place. */
    rpgmapper::model::tile::Tiles replacedTiles;            /**< The tiles replaced. */
    
public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to place the tile.
     * @param   tile            the tile to place.
     * @param   position        position to place the tile.
     */
    PlaceTile(rpgmapper::model::Map * map, rpgmapper::model::tile::TilePointer tile, QPointF position);
    
    /**
     * Constructor.
     *
     * @param   map             the map to place the tile.
     * @param   tile            the tile to place.
     * @param   position        position to place the tile.
     */
    PlaceTile(rpgmapper::model::MapPointer map, rpgmapper::model::tile::TilePointer tile, QPointF position)
        : PlaceTile{map.data(), tile, position} {}
    
    /**
     * Destructor.
     */
    ~PlaceTile() override = default;
    
    /**
     * Executes this command.
     */
    void execute() override;
    
    /**
     * Returns a human readable string for this command.
     *
     * @return  a string describing this command.
     */
    QString getDescription() const override;
    
    /**
     * Undoes the command.
     */
    void undo() override;
};


}


#endif

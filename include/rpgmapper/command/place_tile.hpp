/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_PLACE_TILE_HPP
#define RPGMAPPER_MODEL_COMMAND_PLACE_TILE_HPP

#include <QPointF>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/tile/tile_pointer.hpp>
#include <rpgmapper/tile/tiles.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command places a tile on a map.
 */
class PlaceTile : public Command {
    
    QString mapName;                                    /**< The map to place the tile. */
    QPointF position;                                   /**< Position on the map to place the tile. */
    rpgmapper::model::tile::TilePointer tile;           /**< The tile to place. */
    rpgmapper::model::tile::Tiles replacedTiles;        /**< The tiles replaced. */
    
public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the grid color for.
     * @param   tile            the tile to place.
     * @param   position        position to place the tile.
     */
    PlaceTile(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position);
    
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
}
}


#endif

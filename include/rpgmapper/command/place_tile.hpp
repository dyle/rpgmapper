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
 *
 * This command is subclassed by AdditiveTilePlacer and ExclusiveTilePlacer. It must
 * not be instantiated directly.
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
    
protected:
    
    /**
     * Gets the map name to place tile on.
     *
     * @return  the name of the map to place tile on.
     */
    QString getMapName() const {
        return mapName;
    }
    
    /**
     * Returns the position to place tile on the map.
     *
     * @return  the position to place the tile on the map.
     */
    QPointF getPosition() const {
        return position;
    }
    
    /**
     * Returns the tiles which have been replaced.
     *
     * @return  the tiles which have been replaced.
     */
    rpgmapper::model::tile::Tiles const & getReplacedTiles() const {
        return replacedTiles;
    }
    
    /**
     * Returns the tile which has been placed.
     *
     * @return  the tile which has been placed.
     */
    rpgmapper::model::tile::TilePointer const & getTile() const {
         return tile;
    }
};


}
}
}


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_EXCLUSIVE_TILE_PLACER_HPP
#define RPGMAPPER_MODEL_COMMAND_EXCLUSIVE_TILE_PLACER_HPP

#include <rpgmapper/command/place_tile.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command places a tile on a map exclusively, i.e. it replaces any other tile before.
 */
class ExclusiveTilePlacer : public PlaceTile {
    
public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the grid color for.
     * @param   tile            the tile to place.
     * @param   position        position to place the tile.
     */
    ExclusiveTilePlacer(QString mapName, rpgmapper::model::tile::TilePointer tile, QPointF position);
    
    /**
     * Destructor.
     */
    ~ExclusiveTilePlacer() override = default;
    
    /**
     * Executes this command.
     */
    void execute() override;
    
    /**
     * Undoes the command.
     */
    void undo() override;
};


}
}
}


#endif

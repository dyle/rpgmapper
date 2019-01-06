/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_ERASE_FIELD_HPP
#define RPGMAPPER_MODEL_COMMAND_ERASE_FIELD_HPP

#include <QSharedPointer>
#include <QPointF>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/layer/tile_layer.hpp>
#include <rpgmapper/tile/tiles.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper::model::command {


/**
 * This command erases a field on a map.
 */
class EraseField : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< The map to place the tile. */
    QPointF position;                             /**< Position on the map to place the tile. */
    
    /**
     * All tiles removed at the base layer.
     */
    std::map<unsigned int, rpgmapper::model::tile::Tiles> removedBaseTiles;
    
    /**
     * All tiles removed at the tile layer.
     */
    std::map<unsigned int, rpgmapper::model::tile::Tiles> removedTileTiles;

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to erase a field on.
     * @param   position        position to erase all tiles.
     */
    EraseField(rpgmapper::model::Map * map, QPointF position);
    
    /**
     * Destructor.
     */
    ~EraseField() override = default;
    
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
    
private:
    
    /**
     * Moves all tiles found at our position from a layer into the backup containers.
     *
     * @param   backup      where to move the found tiles to.
     * @param   layers      source layers.
     */
    void remove(std::map<unsigned int, rpgmapper::model::tile::Tiles> & backup,
            std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layers);
    
    /**
     * Undoes the removal of tiles on a layer
     *
     * @param   backup      container holding the files at a layer index.
     * @param   layers      destination layers.
     */
    void undoLayer(std::map<unsigned int, rpgmapper::model::tile::Tiles> & backup,
                std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layers);
};


}


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_GRID_COLOR_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_GRID_COLOR_HPP

#include <QColor>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_pointer.hpp>


namespace rpgmapper::model::command {


/**
 * This command changes the color of a maps grid.
 */
class SetMapGridColor : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< the map to modify. */
    QColor newColor;                              /**< the new grid color. */
    QColor oldColor;                              /**< the old grid color. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the grid color for.
     * @param   newColor        the new grid color.
     */
    SetMapGridColor(rpgmapper::model::Map * map, QColor newColor);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the grid color for.
     * @param   newColor        the new grid color.
     */
    SetMapGridColor(rpgmapper::model::MapPointer map, QColor newColor) : SetMapGridColor{map.data(), newColor} {}
    
    /**
     * Destructor.
     */
    ~SetMapGridColor() override = default;
    
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

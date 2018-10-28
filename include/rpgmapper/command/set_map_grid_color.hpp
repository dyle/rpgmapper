/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_GRID_COLOR_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_GRID_COLOR_HPP


#include <QColor>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the color of a maps grid.
 */
class SetMapGridColor : public Command {

    QString mapName;        /**< the map to modify. */
    QColor newColor;        /**< the new grid color. */
    QColor oldColor;        /**< the old grid color. */

public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the grid color for.
     * @param   newColor        the new grid color.
     */
    SetMapGridColor(QString mapName, QColor newColor);
    
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
}
}


#endif

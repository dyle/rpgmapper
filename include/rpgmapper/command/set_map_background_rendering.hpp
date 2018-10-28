/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_RENDERING_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_RENDERING_HPP


#include <QColor>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command switches between plain color and image background rendering of a map.
 */
class SetMapBackgroundRendering : public Command {

    QString mapName;            /**< the map to modify. */
    QString newRendering;       /**< the new rendering directive. */
    QString oldRendering;       /**< the old rendering directive. */

public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the background rendering.
     * @param   newRendering    the new rendering directive.
     */
    SetMapBackgroundRendering(QString mapName, QString newRendering);
    
    /**
     * Destructor.
     */
    ~SetMapBackgroundRendering() override = default;
    
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

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_MARGINS_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_MARGINS_HPP

#include <QMargins>
#include <QString>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the margin of a map.
 */
class SetMapMargin : public Command {

    QString mapName;             /**< the map to modify. */
    float newMargin;             /**< the new margins of the map. */
    float oldMargin;             /**< the old margins of the map. */

public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the margins for.
     * @param   newMargin       the new margin  value
     */
    SetMapMargin(QString mapName, float newMargin);
    
    /**
     * Destructor.
     */
    ~SetMapMargin() override = default;
    
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
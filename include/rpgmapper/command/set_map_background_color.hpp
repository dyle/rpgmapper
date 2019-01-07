/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_COLOR_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_COLOR_HPP

#include <QColor>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map_pointer.hpp>


// fwd
namespace rpgmapper::model { class Map; }


namespace rpgmapper::model::command {


/**
 * This command changes the color used for drawing a maps background.
 */
class SetMapBackgroundColor : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< the map to change the background color. */
    QColor newColor;                              /**< the new background color. */
    QColor oldColor;                              /**< the old background color. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the background color for.
     * @param   newColor        the new background color.
     */
    SetMapBackgroundColor(rpgmapper::model::Map * map, QColor newColor);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the background color for.
     * @param   newColor        the new background color.
     */
    SetMapBackgroundColor(rpgmapper::model::MapPointer map, QColor newColor)
        : SetMapBackgroundColor{map.data(), newColor} {}
    
    /**
     * Destructor.
     */
    ~SetMapBackgroundColor() override = default;
    
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

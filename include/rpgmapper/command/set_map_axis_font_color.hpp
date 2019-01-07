/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_COLOR_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_COLOR_HPP

#include <QColor>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map_pointer.hpp>


// fwd
namespace rpgmapper::model { class Map; }


namespace rpgmapper::model::command {


/**
 * This command changes the color of the axis font on maps.
 */
class SetMapAxisFontColor : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< the map for which the color is changed. */
    QColor newColor;                              /**< the new color of the axis font. */
    QColor oldColor;                              /**< the old color used. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the font color for.
     * @param   newColor        the new font color.
     */
    SetMapAxisFontColor(rpgmapper::model::Map * map, QColor newColor);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the font color for.
     * @param   newColor        the new font color.
     */
    SetMapAxisFontColor(rpgmapper::model::MapPointer map, QColor newColor)
        : SetMapAxisFontColor{map.data(), newColor} {}
    
    /**
     * Destructor.
     */
    ~SetMapAxisFontColor() override = default;
    
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

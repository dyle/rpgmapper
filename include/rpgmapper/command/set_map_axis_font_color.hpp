/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_COLOR_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_COLOR_HPP


#include <QColor>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the color of the axis font on maps.
 */
class SetMapAxisFontColor : public AtlasCommand {

    QString mapName;            /**< the map for which the color is changed. */
    QColor newColor;            /**< the new color of the axis font. */
    QColor oldColor;            /**< the old color used. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   mapName         the name of the map to change the font color for.
     * @param   newColor        the new font color.
     */
    SetMapAxisFontColor(AtlasPointer & atlas, QString const & mapName, QColor newColor);
    
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
}
}


#endif

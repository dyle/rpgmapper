/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_FONT_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_FONT_HPP

#include <QFont>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the font used for drawing the axis on maps.
 */
class SetMapAxisFont : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< The map to set the axis font for. */
    QFont newFont;                                /**< the new font to use. */
    QFont oldFont;                                /**< the old font. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the font for.
     * @param   newFont         the new font.
     */
    SetMapAxisFont(rpgmapper::model::Map * map, QFont newFont);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the font for.
     * @param   newFont         the new font.
     */
    SetMapAxisFont(rpgmapper::model::MapPointer map, QFont newFont) : SetMapAxisFont{map.data(), newFont} {}
    
    /**
     * Destructor.
     */
    ~SetMapAxisFont() override = default;
    
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

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_FONT_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_FONT_HPP


#include <QFont>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the font used for drawing the axis on maps.
 */
class SetMapAxisFont : public AtlasCommand {

    QString mapName;            /**< the map to change the font for. */
    QFont newFont;              /**< the new font to use. */
    QFont oldFont;              /**< the old font. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   mapName         the name of the map to change the font for.
     * @param   newFont         the new font.
     */
    SetMapAxisFont(AtlasPointer & atlas, QString const & mapName, QFont newFont);
    
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

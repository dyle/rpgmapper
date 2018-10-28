/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_RENDER_MODE_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_RENDER_MODE_HPP


#include <QColor>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/layer/image_render_mode.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the way how the background image is rendered on a map.
 */
class SetMapBackgroundImageRenderMode : public Command {

    QString mapName;                                /**< the map to modify. */
    rpgmapper::model::ImageRenderMode newMode;      /**< the new render mode. */
    rpgmapper::model::ImageRenderMode oldMode;      /**< the old render mode. */

public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the background rendering mode.
     * @param   newMode         the new map background image render mode.
     */
    SetMapBackgroundImageRenderMode(QString mapName, rpgmapper::model::ImageRenderMode newMode);
    
    /**
     * Destructor.
     */
    ~SetMapBackgroundImageRenderMode() override = default;
    
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

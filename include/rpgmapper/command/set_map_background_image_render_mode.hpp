/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_RENDER_MODE_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_RENDER_MODE_HPP

#include <QColor>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/layer/image_render_mode.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_pointer.hpp>


namespace rpgmapper::model::command {


/**
 * This command changes the way how the background image is rendered on a map.
 */
class SetMapBackgroundImageRenderMode : public Command {
    
    rpgmapper::model::Map * map = nullptr;                  /**< the map to modify. */
    rpgmapper::model::layer::ImageRenderMode newMode;       /**< the new render mode. */
    rpgmapper::model::layer::ImageRenderMode oldMode;       /**< the old render mode. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the background rendering mode.
     * @param   newMode         the new map background image render mode.
     */
    SetMapBackgroundImageRenderMode(rpgmapper::model::Map * map, rpgmapper::model::layer::ImageRenderMode newMode);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the background rendering mode.
     * @param   newMode         the new map background image render mode.
     */
    SetMapBackgroundImageRenderMode(rpgmapper::model::MapPointer map, rpgmapper::model::layer::ImageRenderMode newMode)
        : SetMapBackgroundImageRenderMode(map.data(), newMode) {}
    
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


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_HPP

#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the image used as background image on a map.
 */
class SetMapBackgroundImage : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< the map to modify. */
    QString newImage;                             /**< the new background image. */
    QString oldImage;                             /**< the old background image. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the background image for.
     * @param   newImage        the new background image.
     */
    SetMapBackgroundImage(rpgmapper::model::Map * map, QString newImage);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the background image for.
     * @param   newImage        the new background image.
     */
    SetMapBackgroundImage(rpgmapper::model::MapPointer map, QString newImage)
        : SetMapBackgroundImage{map.data(), newImage} {}
    
    /**
     * Destructor.
     */
    ~SetMapBackgroundImage() override = default;
    
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

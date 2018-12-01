/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_HPP

#include <QImage>
#include <QString>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the image used as background image on a map.
 */
class SetMapBackgroundImage : public Command {

    QString mapName;            /**< the map to modify. */
    QImage newImage;            /**< the new background image. */
    QImage oldImage;            /**< the old background image. */

public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the name of the map to change the background image for.
     * @param   newImage        the new background image.
     */
    SetMapBackgroundImage(QString mapName, QImage newImage);
    
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

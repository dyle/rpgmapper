/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_RESIZE_MAP_HPP
#define RPGMAPPER_MODEL_COMMAND_RESIZE_MAP_HPP

#include <QSize>
#include <QString>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * With this class, maps a assigned new dimensions.
 */
class ResizeMap : public Command {

    QString mapName;            /**< The name of the map to resize. */
    QSize newSize;              /**< The new size of the map. */
    QSize oldSize;              /**< The old size of the map. */

public:
    
    /**
     * Constructor.
     *
     * @param   mapName         the map to resize.
     * @param   newSize         the maps new size.
     */
    ResizeMap(QString mapName, QSize newSize);
    
    /**
     * Destructor.
     */
    ~ResizeMap() override = default;
    
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

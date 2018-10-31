/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_MAP_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_MAP_HPP

#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command deletes a map from the atlas.
 */
class RemoveMap : public Command {

    QSharedPointer<Map> map;        /**< The map removed. */
    QString regionName;             /**< The region from which the map is removed. */

public:

    /**
     * Constructor.
     *
     * @param   mapName         the map to remove.
     */
    RemoveMap(QString mapName);
    
    /**
     * Destructor.
     */
    ~RemoveMap() override = default;
    
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

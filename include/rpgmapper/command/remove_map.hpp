/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_MAP_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_MAP_HPP

#include <QSharedPointer>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command deletes a map from the atlas.
 */
class RemoveMap : public Command {

    rpgmapper::model::Map * map = nullptr;              /**< The map removed. */
    rpgmapper::model::Region * region = nullptr;        /**< The region from which the map is removed. */
    rpgmapper::model::MapPointer removedMap;            /**< The removed map as a MapPointer instance. */

public:

    /**
     * Constructor.
     *
     * @param   map         the map to remove.
     */
    RemoveMap(rpgmapper::model::Map * map);
    
    /**
     * Constructor.
     *
     * @param   map         the map to remove.
     */
    RemoveMap(rpgmapper::model::MapPointer map) : RemoveMap(map.data()) {}
    
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

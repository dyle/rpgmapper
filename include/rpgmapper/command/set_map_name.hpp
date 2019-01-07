/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NAME_HPP

#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_pointer.hpp>


namespace rpgmapper::model::command {


/**
 * This class changes the name of a map.
 */
class SetMapName : public Command {
    
    rpgmapper::model::Map * map = nullptr;      /**< the map to change to name. */
    QString newName;                            /**< the new name of the map. */
    QString oldName;                            /**< the old name of the map. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the name for.
     * @param   newName         the new name of the map.
     */
    SetMapName(rpgmapper::model::Map * map, QString newName);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the name for.
     * @param   newName         the new name of the map.
     */
    SetMapName(rpgmapper::model::MapPointer map, QString newName) : SetMapName{map.data(), newName} {}
    
    /**
     * Destructor.
     */
    ~SetMapName() override = default;
    
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

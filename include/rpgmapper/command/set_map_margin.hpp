/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_MARGINS_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_MARGINS_HPP

#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map_pointer.hpp>


// fwd
namespace rpgmapper::model { class Map; }


namespace rpgmapper::model::command {


/**
 * This command changes the margin of a map.
 */
class SetMapMargin : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< the map to modify. */
    float newMargin;                              /**< the new margins of the map. */
    float oldMargin;                              /**< the old margins of the map. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the margins for.
     * @param   newMargin       the new margin  value
     */
    SetMapMargin(rpgmapper::model::Map * map, float newMargin);
    
    /**
     * Constructor.
     *
     * @param   map             the map to change the margins for.
     * @param   newMargin       the new margin  value
     */
    SetMapMargin(rpgmapper::model::MapPointer map, float newMargin) : SetMapMargin{map.data(), newMargin} {}
    
    /**
     * Destructor.
     */
    ~SetMapMargin() override = default;
    
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

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_CREATE_MAP_HPP
#define RPGMAPPER_MODEL_COMMAND_CREATE_MAP_HPP

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command create a new map and adds it to the atlas in a region.
 */
class CreateMap : public Command {

    QString mapName;                /**< the name of the map. */
    QString regionName;             /**< the name of the region. */

public:

    /**
     * Creates a new map.
     *
     * @param   regionName      the name of the region to add the map to.
     * @param   mapName         the name of the map.
     */
    CreateMap(QString const & regionName, QString const & mapName);

    /**
     * Destructor.
     */
    ~CreateMap() override = default;

    /**
     * Executes this command.
     */
    void execute() override;

    /**
     * Returns a human readable string of this command.
     *
     * @return  a string describing this command.
     */
    QString getDescription() const override;

    /**
     * Undoes this command.
     */
    void undo() override;
};


}
}
}


#endif

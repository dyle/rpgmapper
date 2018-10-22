/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_MAP_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_MAP_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command deletes a map from the atlas.
 */
class RemoveMap : public AtlasCommand {

    QString mapName;                /**< The map to remove. */
    QString regionName;             /**< The region from which the map is removed. */

public:

    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   regionName      the region of the map.
     * @param   mapName         the map to remove.
     */
    RemoveMap(AtlasPointer & atlas, QString const & regionName, QString const & mapName);
    
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

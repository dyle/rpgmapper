/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP

#include <rpgmapper/command/composite_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This class deletes a region from the atlas.
 */
class RemoveRegion : public CompositeCommand {

    QString regionName;         /**< The name of the region to delete. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   regionName      the region to delete.
     */
    RemoveRegion(AtlasPointer & atlas, QString const & regionName);
    
    /**
     * Destructor.
     */
    ~RemoveRegion() override = default;
    
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

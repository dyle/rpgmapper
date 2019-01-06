/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP

#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/region.hpp>


namespace rpgmapper::model::command {


/**
 * This class deletes a region from the atlas.
 */
class RemoveRegion : public Command {
    
    rpgmapper::model::Region * region = nullptr;            /**< The region removed. */
    rpgmapper::model::RegionPointer removedRegion;          /**< The removed region as a RegionPointer. */

public:
    
    /**
     * Constructor.
     *
     * @param   region          the region to delete.
     */
    RemoveRegion(rpgmapper::model::Region * region);
    
    /**
     * Constructor.
     *
     * @param   region          the region to delete.
     */
    RemoveRegion(rpgmapper::model::RegionPointer region) : RemoveRegion{region.data()} {}
    
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


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_REGION_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_REGION_NAME_HPP

#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/region_pointer.hpp>


namespace rpgmapper::model::command {


/**
 * This command changes the name of a region in the atlas.
 */
class SetRegionName : public Command {
    
    rpgmapper::model::Region * region = nullptr;        /**< Region to modify */
    QString newName;                                    /**< the new name of the region. */
    QString oldName;                                    /**< the old name of the region. */

public:
    
    /**
     * Constructor.
     *
     * @param   region          the region to modify.
     * @param   newName         the regions new name.
     */
    SetRegionName(rpgmapper::model::Region * region, QString newName);
    
    /**
     * Constructor.
     *
     * @param   region          the region to modify.
     * @param   newName         the regions new name.
     */
    SetRegionName(rpgmapper::model::RegionPointer region, QString newName) : SetRegionName{region.data(), newName} {}
    
    /**
     * Destructor.
     */
    ~SetRegionName() override = default;
    
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

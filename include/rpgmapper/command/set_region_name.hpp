/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_REGION_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_REGION_NAME_HPP

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the name of a region in the atlas.
 */
class SetRegionName : public Command {

    QString newName;        /**< the new name of the region. */
    QString oldName;        /**< the old name of the region. */

public:
    
    /**
     * Constructor.
     *
     * @param   oldName         the regions old name.
     * @param   newName         the regions new name.
     */
    SetRegionName(QString oldName, QString newName);
    
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
}
}


#endif

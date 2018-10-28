/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_CREATE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_CREATE_REGION_HPP

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command creates a new region in the atlas.
 */
class CreateRegion : public Command {

    QString name;           /**< The name of the region to create. */

public:

    /**
     * Constructor.
     *
     * @param   name        the name of the region to create.
     */
    CreateRegion(QString const & name);

    /**
     * Destructor.
     */
    ~CreateRegion() override = default;

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

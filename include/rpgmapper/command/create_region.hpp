/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_CREATE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_CREATE_REGION_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command creates a new region in the atlas.
 */
class CreateRegion : public AtlasCommand {

    QString name;           /**< The name of the region to create. */

public:

    /**
     * Constructor.
     *
     * @param   atlas       the atlas we are currently working on.
     * @param   name        the name of the region to create.
     */
    CreateRegion(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & name);

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

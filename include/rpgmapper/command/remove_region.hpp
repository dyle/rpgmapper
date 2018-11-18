/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP

#include <set>

#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This class deletes a region from the atlas.
 */
class RemoveRegion : public Command {

    QSharedPointer<Region> region;              /**< The region removed. */

public:
    
    /**
     * Constructor.
     *
     * @param   name        the name of the region to delete.
     */
    RemoveRegion(QString name);
    
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

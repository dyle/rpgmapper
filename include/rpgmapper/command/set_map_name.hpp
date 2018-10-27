/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NAME_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This class changes the name of a map.
 */
class SetMapName : public AtlasCommand {

    QString newName;        /**< the new name of the map. */
    QString oldName;        /**< the old name of the map. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   oldName         the old name of the map.
     * @param   newName         the new name of the map.
     */
    SetMapName(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & oldName, QString const & newName);
    
    /**
     * Destructor.
     */
    ~SetMapName() override = default;
    
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

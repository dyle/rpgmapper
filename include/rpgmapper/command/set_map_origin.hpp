/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_ORIGINHPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_ORIGINHPP

#include <QString>

#include <rpgmapper/command/atlas_command.hpp>
#include <rpgmapper/coordinate_system.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command lets the maps origin move around.
 */
class SetMapOrigin : public AtlasCommand {

    QString mapName;                    /**< the map to modify. */
    CoordinatesOrigin newOrigin;        /**< the new origin of the map. */
    CoordinatesOrigin oldOrigin;        /**< the maps old origin. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   mapName         the name of the map to modify.
     * @param   origin          the new origin of the map.
     */
    SetMapOrigin(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, rpgmapper::model::CoordinatesOrigin origin);
    
    /**
     * Destructor.
     */
    ~SetMapOrigin() override = default;
    
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

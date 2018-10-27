/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_AXIS_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_AXIS_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {



/**
 * This class changes how the axis numerals are drawn on the map.
 */
class SetMapNumeralAxis : public AtlasCommand {

    QString mapName;            /**< the map to modify. */
    bool xAxis;                 /**< flag for X-axis (if false, then Y-axis is targeted). */
    QString newNumeral;         /**< the new numeral setting. */
    QString oldNumeral;         /**< the old numeral setting. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   mapName         the name of the map to modify.
     * @param   xAxis           true, for X-axis, false for Y-axis.
     * @param   newNumeral      the new numeral setting for the maps axis.
     */
    SetMapNumeralAxis(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, bool xAxis, QString newNumeral);
    
    /**
     * Destructor.
     */
    ~SetMapNumeralAxis() override = default;
    
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

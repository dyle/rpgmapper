/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_OFFSET_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_OFFSET_HPP

#include <QPointF>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This command changes the offset values on the axis of a map.
 */
class SetMapNumeralOffset : public AtlasCommand {

    QString mapName;            /**< the map to modify. */
    QPointF newOffset;          /**< the new offset values. */
    QPointF oldOffset;          /**< the old offset values. */

public:
    
    /**
     * Constructor.
     *
     * @param   atlas           the current atlas.
     * @param   mapName         the name of the map to modify.
     * @param   newOffset       the new offset values of the map.
     */
    SetMapNumeralOffset(QSharedPointer<rpgmapper::model::Atlas> & atlas, QString const & mapName, QPointF newOffset);
    
    /**
     * Destructor.
     */
    ~SetMapNumeralOffset() override = default;
    
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

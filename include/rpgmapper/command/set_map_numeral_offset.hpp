/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_OFFSET_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_OFFSET_HPP

#include <QPointF>
#include <QString>

#include <rpgmapper/command/command.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_pointer.hpp>


namespace rpgmapper::model::command {


/**
 * This command changes the offset values on the axis of a map.
 */
class SetMapNumeralOffset : public Command {
    
    rpgmapper::model::Map * map = nullptr;        /**< the map to modify. */
    QPointF newOffset;                            /**< the new offset values. */
    QPointF oldOffset;                            /**< the old offset values. */

public:
    
    /**
     * Constructor.
     *
     * @param   map             the map to modify.
     * @param   newOffset       the new offset values of the map.
     */
    SetMapNumeralOffset(rpgmapper::model::Map * map, QPointF newOffset);
    
    /**
     * Constructor.
     *
     * @param   map             the map to modify.
     * @param   newOffset       the new offset values of the map.
     */
    SetMapNumeralOffset(rpgmapper::model::MapPointer map, QPointF newOffset)
        : SetMapNumeralOffset{map.data(), newOffset} {}
    
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


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/field.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::tile;

/**
 * The very maximum dimension value we support regardless of the maximum size of a map.
 */
static int MAX_DIMENSION_VALUE = 1000000;


Field::Field(int x, int y) : Field{QPoint(x, y)} {
}


Field::Field(QPoint const & position) : position(position) {
}


Field::Field(QPointF const & position) : Field{static_cast<int>(position.x()), static_cast<int>(position.y())} {
}


int Field::getIndex(int x, int y) {
    return y * MAX_DIMENSION_VALUE + x;
}


QPoint Field::getPositionFromIndex(int index) {
    return {index / MAX_DIMENSION_VALUE, index % MAX_DIMENSION_VALUE};
}


bool Field::isTilePresent(rpgmapper::model::tile::Tile const * tile) const {
    
    if (!tile) {
        return false;
    }
    
    for (auto && tileIter : getTiles()) {
        if ((*tileIter.data()) == (*tile)) {
            return true;
        }
    }
    
    return false;
}


Field const & Field::nullField() {
    static InvalidField nullField;
    return nullField;
}

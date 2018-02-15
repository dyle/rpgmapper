/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


Coordinates CoordinateSystem::transpose(QPoint const & position) const {

    Coordinates coordinate;

    switch (getOrigin()) {

        case CoordinateOrigin::bottomLeft:
            coordinate = Coordinates{position.x(), getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::bottomRight:
            coordinate = Coordinates{getSize().width() - position.x() - 1, getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinateOrigin::topRight:
            coordinate = Coordinates{getSize().width() - position.x() - 1, position.y()};
            break;
    }

    return coordinate;
}


CoordinatesF CoordinateSystem::transpose(QPointF const & position) const{

    CoordinatesF coordinate;

    switch (getOrigin()) {

        case CoordinateOrigin::bottomLeft:
            coordinate = CoordinatesF{position.x(), getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::bottomRight:
            coordinate = CoordinatesF{getSize().width() - position.x() - 1, getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinateOrigin::topRight:
            coordinate = CoordinatesF{getSize().width() - position.x() - 1, position.y()};
            break;
    }

    return coordinate;
}


void CoordinateSystem::resize(QSize const & size) {
    if ((size.width() < getMinimumSize().width()) || (size.height() < getMinimumSize().height())) {
        return;
    }
    if ((size.width() > getMaximumSize().width()) || (size.height() > getMaximumSize().height())) {
        return;
    }
    this->size = size;
}

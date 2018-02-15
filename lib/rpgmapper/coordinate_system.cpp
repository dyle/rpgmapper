/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


UserCoordinate CoordinateSystem::transpose(ScreenCoordinate const & position) const {

    UserCoordinate coordinate;

    switch (getOrigin()) {

        case CoordinateOrigin::bottomLeft:
            coordinate = UserCoordinate{position.x(), getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::bottomRight:
            coordinate = UserCoordinate{getSize().width() - position.x() - 1, getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinateOrigin::topRight:
            coordinate = UserCoordinate{getSize().width() - position.x() - 1, position.y()};
            break;
    }

    return coordinate;
}


UserCoordinateF CoordinateSystem::transpose(ScreenCoordinateF const & position) const{

    UserCoordinateF coordinate;

    switch (getOrigin()) {

        case CoordinateOrigin::bottomLeft:
            coordinate = UserCoordinateF{position.x(), getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::bottomRight:
            coordinate = UserCoordinateF{getSize().width() - position.x() - 1, getSize().height() - position.y() - 1};
            break;

        case CoordinateOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinateOrigin::topRight:
            coordinate = UserCoordinateF{getSize().width() - position.x() - 1, position.y()};
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

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
            // TODO
            break;

        case CoordinateOrigin::bottomRight:
            // TODO
            break;

        case CoordinateOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinateOrigin::topRight:
            // TODO
            break;
    }

    return coordinate;
}


UserCoordinateF CoordinateSystem::transpose(ScreenCoordinateF const & position) const{

    UserCoordinateF coordinate;

    switch (getOrigin()) {

        case CoordinateOrigin::bottomLeft:
            // TODO
            break;

        case CoordinateOrigin::bottomRight:
            // TODO
            break;

        case CoordinateOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinateOrigin::topRight:
            // TODO
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

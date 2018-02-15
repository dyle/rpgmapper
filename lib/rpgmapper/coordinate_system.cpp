/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


CoordinateSystem::CoordinateSystem() {
    numeralXAxis = NumeralConverter::create("Numeric");
    if (!numeralXAxis->isValid()) {
        throw std::runtime_error("Failed to create default numeral converter for X axis.");
    }
    numeralYAxis = NumeralConverter::create("Numeric");
    if (!numeralYAxis->isValid()) {
        throw std::runtime_error("Failed to create default numeral converter for Y axis.");
    }
}


NumeralCoordinate CoordinateSystem::getNumeralCoordinates(QPoint position) const {
    return NumeralCoordinate{numeralXAxis->convert(position.x()), numeralYAxis->convert(position.y())};
}


void CoordinateSystem::setNumeralXAxis(QString numeral) {
    auto const & numeralConverter = NumeralConverter::create(numeral);
    if (numeralConverter->isValid()) {
        numeralXAxis = numeralConverter;
    }
}


void CoordinateSystem::setNumeralYAxis(QString numeral) {
    auto const & numeralConverter = NumeralConverter::create(numeral);
    if (numeralConverter->isValid()) {
        numeralYAxis = numeralConverter;
    }
}


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

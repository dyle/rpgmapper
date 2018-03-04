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


NumeralCoordinates CoordinateSystem::getNumeralCoordinates(QPoint position) const {
    return NumeralCoordinates{numeralXAxis->convert(position.x()), numeralYAxis->convert(position.y())};
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


QPoint CoordinateSystem::transpose(QPoint const & position) const {

    QPoint coordinate;

    switch (getOrigin()) {

        case CoordinatesOrigin::bottomLeft:
            coordinate = QPoint{position.x(), getSize().height() - position.y() - 1};
            break;

        case CoordinatesOrigin::bottomRight:
            coordinate = QPoint{getSize().width() - position.x() - 1, getSize().height() - position.y() - 1};
            break;

        case CoordinatesOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinatesOrigin::topRight:
            coordinate = QPoint{getSize().width() - position.x() - 1, position.y()};
            break;
    }

    return coordinate;
}


QPointF CoordinateSystem::transpose(QPointF const & position) const {

    QPointF coordinate;

    switch (getOrigin()) {

        case CoordinatesOrigin::bottomLeft:
            coordinate = QPointF{position.x(), getSize().height() - position.y() - 1};
            break;

        case CoordinatesOrigin::bottomRight:
            coordinate = QPointF{getSize().width() - position.x() - 1, getSize().height() - position.y() - 1};
            break;

        case CoordinatesOrigin::topLeft:
            coordinate = position;
            break;

        case CoordinatesOrigin::topRight:
            coordinate = QPointF{getSize().width() - position.x() - 1, position.y()};
            break;
    }

    return coordinate;
}


QPoint CoordinateSystem::transposeToMapCoordinates(QPoint const & position) const {
    return transpose(position) + getOffset();
}


QPointF CoordinateSystem::transposeToMapCoordinates(QPointF const & position) const{
    return transpose(position) + getOffsetF();
}


QPoint CoordinateSystem::transposeToScreenCoordinates(QPoint const & position) const {
    return transpose(position) - getOffset();
}


QPointF CoordinateSystem::transposeToScreenCoordinates(QPointF const & position) const{
    return transpose(position) - getOffsetF();
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

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


QString rpgmapper::model::coordinatesOriginToString(rpgmapper::model::CoordinatesOrigin origin) {

    static std::map<rpgmapper::model::CoordinatesOrigin, QString> const originNames{
        {rpgmapper::model::CoordinatesOrigin::topLeft, "topLeft"},
        {rpgmapper::model::CoordinatesOrigin::topRight, "topRight"},
        {rpgmapper::model::CoordinatesOrigin::bottomLeft, "bottomLeft"},
        {rpgmapper::model::CoordinatesOrigin::bottomRight, "bottomRight"}
    };

    auto pair = originNames.find(origin);
    if (pair == originNames.end()) {
        throw std::out_of_range("Name for given coordinate origin not found.");
    }
    return (*pair).second;
}


rpgmapper::model::CoordinatesOrigin rpgmapper::model::stringToCoordinatesOrigin(QString const & string) {

    static std::map<QString, rpgmapper::model::CoordinatesOrigin> const originNames{
        {"topLeft", rpgmapper::model::CoordinatesOrigin::topLeft},
        {"topRight", rpgmapper::model::CoordinatesOrigin::topRight},
        {"bottomLeft", rpgmapper::model::CoordinatesOrigin::bottomLeft},
        {"bottomRight", rpgmapper::model::CoordinatesOrigin::bottomRight, }
    };

    auto pair = originNames.find(string);
    if (pair == originNames.end()) {
        throw std::out_of_range("Cannot convert given coordinate origin to a name.");
    }
    return (*pair).second;
}


CoordinateSystem::CoordinateSystem() {

    numeralXAxis = NumeralConverter::create("numeric");
    if (!numeralXAxis->isValid()) {
        throw std::runtime_error("Failed to create default numeral converter for X axis.");
    }

    numeralYAxis = NumeralConverter::create("numeric");
    if (!numeralYAxis->isValid()) {
        throw std::runtime_error("Failed to create default numeral converter for Y axis.");
    }
}


QJsonObject CoordinateSystem::getJsonObject() const {

    QJsonObject jsonObject;
    jsonObject["origin"] = coordinatesOriginToString(origin);

    QJsonObject jsonSize;
    jsonSize["width"] = size.width();
    jsonSize["height"] = size.height();
    jsonObject["size"] = jsonSize;

    QJsonObject jsonOffset;
    jsonOffset["x"] = offset.x();
    jsonOffset["y"] = offset.y();
    jsonObject["offset"] = jsonOffset;

    QJsonObject jsonNumerals;
    jsonNumerals["x"] = numeralXAxis->getName();
    jsonNumerals["y"] = numeralYAxis->getName();
    jsonObject["numerals"] = jsonNumerals;

    return jsonObject;
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

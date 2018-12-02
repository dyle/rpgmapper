/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

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


bool CoordinateSystem::applyJSON(QJsonObject const & json) {
    
    if (json.contains("origin") && json["origin"].isString()) {
        origin = stringToCoordinatesOrigin(json["origin"].toString());
    }
    
    if (json.contains("size") && json["size"].isObject() && !applyJSONSize(json["size"].toObject())) {
        return false;
    }
    
    if (json.contains("margin") && json["margin"].isDouble()) {
        auto newMargin = static_cast<float>(json["margin"].toDouble());
        if (newMargin >= 0.0) {
            margin = newMargin;
        }
    }

    if (json.contains("offset") && json["offset"].isObject() && !applyJSONOffset(json["offset"].toObject())) {
        return false;
    }
    
    if (json.contains("numerals") && json["numerals"].isObject()) {
        return applyJSONNumerals(json["numerals"].toObject());
    }
    
    return true;
}


bool CoordinateSystem::applyJSONNumerals(QJsonObject const & json) {

    if (json.contains("x") && json["x"].isString()) {
        auto numeralXAxis = NumeralConverter::create(json["x"].toString());
        if (!numeralXAxis->isValid()) {
            return false;
        }
        this->numeralXAxis = numeralXAxis;
    }
    if (json.contains("y") && json["y"].isString()) {
        auto numeralYAxis = NumeralConverter::create(json["y"].toString());
        if (!numeralYAxis->isValid()) {
            return false;
        }
        this->numeralYAxis = numeralYAxis;
    }

    return true;
}


bool CoordinateSystem::applyJSONOffset(QJsonObject const & json) {
    
    if (json.contains("x") && json["x"].isDouble()) {
        offset.setX(json["x"].toDouble());
    }
    if (json.contains("y") && json["y"].isDouble()) {
        offset.setY(json["y"].toDouble());
    }
    return true;
}


bool CoordinateSystem::applyJSONSize(QJsonObject const & json) {

    QSize size;

    if (json.contains("width") && json["width"].isDouble()) {
        size.setWidth(static_cast<int>(json["width"].toDouble()));
    }
    if (json.contains("height") && json["height"].isDouble()) {
        size.setHeight(static_cast<int>(json["height"].toDouble()));
    }

    if (size.width() < getMinimumSize().width() || size.width() >= getMaximumSize().width()) {
        return false;
    }
    if (size.height() < getMinimumSize().height() || size.height() >= getMaximumSize().height()) {
        return false;
    }

    this->size = size;

    return true;
}


QRect CoordinateSystem::getInnerRect(int tileSize) const {
    
    QRect rect{0, 0, 0, 0};
    QSize size = getSize();
    
    int axisLabelHeight = tileSize;
    int marginHeight = static_cast<int>(getMargin() * tileSize);
    int axisLabelWidth = tileSize;
    int marginWidth = static_cast<int>(getMargin() * tileSize);
    
    rect.setX(axisLabelWidth + marginWidth);
    rect.setY(axisLabelHeight + marginHeight);
    rect.setHeight(size.height() * tileSize);
    rect.setWidth(size.width() * tileSize);
    
    return rect;
}


QJsonObject CoordinateSystem::getJSON() const {

    QJsonObject json;
    json["origin"] = coordinatesOriginToString(origin);

    QJsonObject jsonSize;
    jsonSize["width"] = size.width();
    jsonSize["height"] = size.height();
    json["size"] = jsonSize;
    
    json["margin"] = margin;

    QJsonObject jsonOffset;
    jsonOffset["x"] = offset.x();
    jsonOffset["y"] = offset.y();
    json["offset"] = jsonOffset;

    QJsonObject jsonNumerals;
    jsonNumerals["x"] = numeralXAxis->getName();
    jsonNumerals["y"] = numeralYAxis->getName();
    json["numerals"] = jsonNumerals;

    return json;
}


NumeralCoordinates CoordinateSystem::getNumeralCoordinates(QPoint position) const {
    return NumeralCoordinates{numeralXAxis->convert(position.x()), numeralYAxis->convert(position.y())};
}


QRect CoordinateSystem::getOuterRect(int tileSize) const {
    
    QRect rect{0, 0, 0, 0};
    QSize size = getSize();
    
    int axisLabelHeight = tileSize;
    int marginHeight = static_cast<int>(getMargin() * tileSize);
    int axisLabelWidth = tileSize;
    int marginWidth = static_cast<int>(getMargin() * tileSize);
    
    rect.setHeight(size.height() * tileSize + axisLabelHeight * 2 + marginHeight * 2);
    rect.setWidth(size.width() * tileSize + axisLabelWidth * 2 + marginWidth * 2);
    
    return rect;
}


bool CoordinateSystem::isValidSize(QSize size) {
    
    if ((size.width() < getMinimumSize().width()) || (size.height() < getMinimumSize().height())) {
        return false;
    }
    if ((size.width() > getMaximumSize().width()) || (size.height() > getMaximumSize().height())) {
        return false;
    }
    
    return true;
}


void CoordinateSystem::setMargin(float newMargin) {
    if ((newMargin >= 0.0) && (newMargin != margin)) {
        margin = newMargin;
        emit marginChanged();
    }
}


void CoordinateSystem::setNumeralXAxis(QString numeral) {
    auto const & numeralConverter = NumeralConverter::create(std::move(numeral));
    if (numeralConverter->isValid()) {
        numeralXAxis = numeralConverter;
        emit numeralXAxisChanged();
    }
}


void CoordinateSystem::setNumeralYAxis(QString numeral) {
    auto const & numeralConverter = NumeralConverter::create(std::move(numeral));
    if (numeralConverter->isValid()) {
        numeralYAxis = numeralConverter;
        emit numeralYAxisChanged();
    }
}

void CoordinateSystem::setOffset(QPointF offset) {
    
    if (this->offset != offset) {
        this->offset = offset;
        emit offsetChanged(offset);
    }
}


void CoordinateSystem::setOrigin(CoordinatesOrigin origin) {
    if (this->origin != origin) {
        this->origin = origin;
        emit originChanged(origin);
    }
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


QPointF CoordinateSystem::transposeToMapCoordinates(QPointF position) const{
    return transpose(position) + getOffset();
}


QPointF CoordinateSystem::transposeToScreenCoordinates(QPointF position) const{
    return transpose(position) - getOffset();
}


void CoordinateSystem::resize(QSize size) {
    if (isValidSize(size)) {
        this->size = size;
        emit sizeChanged(size);
    }
}

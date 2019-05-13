/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_json.hpp>
#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


QString rpgmapper::model::coordinatesOriginToString(rpgmapper::model::CoordinatesOrigin origin) {

    static std::map<rpgmapper::model::CoordinatesOrigin, QString> const originNames {
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

    static std::map<QString, rpgmapper::model::CoordinatesOrigin> const originNames {
        {"topLeft", rpgmapper::model::CoordinatesOrigin::topLeft},
        {"topRight", rpgmapper::model::CoordinatesOrigin::topRight},
        {"bottomLeft", rpgmapper::model::CoordinatesOrigin::bottomLeft},
        {"bottomRight", rpgmapper::model::CoordinatesOrigin::bottomRight}
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


void CoordinateSystem::applyJson(QJsonObject const & json) {
    
    if (json.contains("origin")) {
        applyJsonOrigin(json["origin"]);
    }

    if (json.contains("size")) {
        applyJsonSize(json["size"]);
    }

    if (json.contains("margin")) {
        applyJsonMargin(json["margin"]);
    }

    if (json.contains("offset")) {
        applyJsonOffset(json["offset"]);
    }

    if (json.contains("numerals")) {
        applyJsonNumerals(json["numerals"]);
    }
}


void CoordinateSystem::applyJsonMargin(QJsonValue const & json) {

    if (!json.isDouble()) {
        throw rpgmapper::model::exception::invalid_json{"'margin' attribute is not a float."};
    }

    auto newMargin = static_cast<float>(json.toDouble());
    if (newMargin >= 0.0) {
        setMargin(newMargin);
    }
}


void CoordinateSystem::applyJsonNumerals(QJsonValue const & json) {

    if (!json.isObject()) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute is not an object."};
    }

    auto jsonObject = json.toObject();

    if (!jsonObject.contains("x")) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute does not contains 'x' value."};
    }
    if (!jsonObject["x"].isString()) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute 'x' value is not a string."};
    }

    if (!jsonObject.contains("y")) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute does not contains 'y' value."};
    }
    if (!jsonObject["y"].isString()) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute 'y' value is not a string."};
    }

    auto numeralXAxis = NumeralConverter::create(jsonObject["x"].toString());
    if (!numeralXAxis->isValid()) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute 'x' value is invalid."};
    }
    auto numeralYAxis = NumeralConverter::create(jsonObject["y"].toString());
    if (!numeralYAxis->isValid()) {
        throw rpgmapper::model::exception::invalid_json{"'numerals' attribute 'y' value is invalid."};
    }

    setNumeralAxis(numeralXAxis, numeralYAxis);
}


void CoordinateSystem::applyJsonOffset(QJsonValue const & json) {

    if (!json.isObject()) {
        throw rpgmapper::model::exception::invalid_json{"'offset' attribute is not an object."};
    }

    auto jsonObject = json.toObject();

    if (!jsonObject.contains("x")) {
        throw rpgmapper::model::exception::invalid_json{"'offset' attribute does not contains 'x' value."};
    }
    if (!jsonObject["x"].isDouble()) {
        throw rpgmapper::model::exception::invalid_json{"'offset' attribute 'x' value is not a float."};
    }

    if (!jsonObject.contains("y")) {
        throw rpgmapper::model::exception::invalid_json{"'offset' attribute does not contains 'y' value."};
    }
    if (!jsonObject["y"].isDouble()) {
        throw rpgmapper::model::exception::invalid_json{"'offset' attribute 'y' value is not a float."};
    }

    setOffset(QPointF{jsonObject["x"].toDouble(), jsonObject["y"].toDouble()});
}


void CoordinateSystem::applyJsonOrigin(QJsonValue const & json) {

    if (!json.isString()) {
        throw rpgmapper::model::exception::invalid_json{"Invalid value for coordinate system origin."};
    }
    setOrigin(stringToCoordinatesOrigin(json.toString()));
}


void CoordinateSystem::applyJsonSize(QJsonValue const & json) {

    if (!json.isObject()) {
        throw rpgmapper::model::exception::invalid_json{"Invalid value for coordinate system size."};
    }

    auto jsonObject = json.toObject();
    QSize size;

    if (jsonObject.contains("width") && jsonObject["width"].isDouble()) {
        size.setWidth(static_cast<int>(jsonObject["width"].toDouble()));
    }
    if (jsonObject.contains("height") && jsonObject["height"].isDouble()) {
        size.setHeight(static_cast<int>(jsonObject["height"].toDouble()));
    }

    if (size.width() < getMinimumSize().width() || size.width() >= getMaximumSize().width()) {
        throw rpgmapper::model::exception::invalid_json{"Coordinate system width is out of bounds."};
    }
    if (size.height() < getMinimumSize().height() || size.height() >= getMaximumSize().height()) {
        throw rpgmapper::model::exception::invalid_json{"Coordinate system height is out of bounds."};
    }

    resize(size);
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


QJsonObject CoordinateSystem::getJson() const {

    QJsonObject json;
    json["origin"] = coordinatesOriginToString(origin);

    QJsonObject jsonSize = {{"width", size.width()}, {"height", size.height()}};
    json["size"] = jsonSize;
    
    json["margin"] = margin;

    QJsonObject jsonOffset= {{"x", offset.x()}, {"y", offset.y()}};
    json["offset"] = jsonOffset;

    QJsonObject jsonNumerals {{"x", numeralXAxis->getName()}, {"y", numeralYAxis->getName()}};
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


QRect CoordinateSystem::getRect() const {
    return QRect{static_cast<int>(offset.x()), static_cast<int>(offset.y()), size.width(), size.height()};
}


bool CoordinateSystem::isAxisLeftToRight() const {
    return getOrigin() == CoordinatesOrigin::topLeft || getOrigin() == CoordinatesOrigin::bottomLeft;
}


bool CoordinateSystem::isAxisTopToDown() const {
    return getOrigin() == CoordinatesOrigin::topLeft || getOrigin() == CoordinatesOrigin::topRight;
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


void CoordinateSystem::resize(QSize size) {
    if (isValidSize(size)) {
        this->size = size;
        emit sizeChanged(size);
    }
}


void CoordinateSystem::setMargin(float newMargin) {
    if ((newMargin >= 0.0) && (newMargin != margin)) {
        margin = newMargin;
        emit marginChanged();
    }
}


void CoordinateSystem::setNumeralAxis(QSharedPointer<rpgmapper::model::NumeralConverter> numeralXAxis,
                                      QSharedPointer<rpgmapper::model::NumeralConverter> numeralYAxis) {
    this->numeralXAxis = numeralXAxis;
    this->numeralYAxis = numeralYAxis;
    emit numeralXAxisChanged();
    emit numeralYAxisChanged();
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


QPoint CoordinateSystem::translateToMap(QPoint point) const {
    
    int x = point.x();
    int y = point.y();
    auto size = getSize();
    
    if (!isAxisLeftToRight()) {
        x = size.width() - 1 - x;
    }
    if (!isAxisTopToDown()) {
        y = size.height() - 1 - y;
    }
    
    auto offset = getOffset();
    x += static_cast<int>(offset.x());
    y += static_cast<int>(offset.y());
    
    return QPoint{x, y};
}

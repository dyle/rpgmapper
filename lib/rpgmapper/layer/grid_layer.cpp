/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model::layer;


/**
 * Default color of the grid on the map.
 */
static char const * DEFAULT_GRID_COLOR = "#0022ff";


GridLayer::GridLayer(Map * map) : Layer{map} {
    getAttributes()["color"] = DEFAULT_GRID_COLOR;
}


void GridLayer::draw(QPainter & painter, int tileSize) const {
    drawXAxis(painter, tileSize);
    drawYAxis(painter, tileSize);
    drawBorder(painter, tileSize);
}


void GridLayer::drawBorder(QPainter & painter, int tileSize) const {
    
    auto map = getMap();
    if (!map) {
        throw exception::invalid_map{};
    }
    
    auto rect = map->getCoordinateSystem()->getInnerRect(tileSize);
    painter.setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawRect(rect);

    auto nOuterTickLength = tileSize / 4;
    for (int x = 0; x <= rect.width(); x += tileSize) {
        painter.drawLine(rect.x() + x, rect.y() - nOuterTickLength, rect.x() + x, rect.y());
        painter.drawLine(rect.x() + x, rect.bottom(), rect.x() + x, rect.bottom() + nOuterTickLength);
    }
    for (int y = 0; y <= rect.height(); y += tileSize) {
        painter.drawLine(rect.x() - nOuterTickLength, rect.y() + y, rect.x(), rect.y() + y);
        painter.drawLine(rect.right(), rect.y() + y, rect.right() + nOuterTickLength, rect.y() + y);
    }
}


void GridLayer::drawXAxis(QPainter & painter, int tileSize) const {
    
    auto map = getMap();
    if (!map) {
        throw exception::invalid_map{};
    }
    
    auto rect = map->getCoordinateSystem()->getInnerRect(tileSize);
    painter.setPen(QPen(getColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int y = tileSize; y <= rect.height() - tileSize; y += tileSize) {
        painter.drawLine(rect.x(), rect.y() + y, rect.x() + rect.width(), rect.y() + y);
    }
}


void GridLayer::drawYAxis(QPainter & painter, int tileSize) const {
    
    auto map = getMap();
    if (!map) {
        throw exception::invalid_map{};
    }
    
    auto rect = map->getCoordinateSystem()->getInnerRect(tileSize);
    painter.setPen(QPen(getColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int x = tileSize; x <= rect.width() - tileSize; x += tileSize) {
        painter.drawLine(rect.x() + x, rect.y(), rect.x() + x, rect.y() + rect.height());
    }
}


QColor GridLayer::getColor() const {
    auto iter = getAttributes().find("color");
    if (iter != getAttributes().end()) {
        return QColor{(*iter).second};
    }
    return QColor{DEFAULT_GRID_COLOR};
}


QJsonObject GridLayer::getJSON() const {
    QJsonObject jsonObject = Layer::getJSON();
    jsonObject["color"] = getColor().name(QColor::HexArgb);
    return jsonObject;
}


void GridLayer::setColor(QColor color) {
    if (getColor() != color) {
        getAttributes()["color"] = color.name(QColor::HexArgb);
        emit gridColorChanged(color);
    }
}

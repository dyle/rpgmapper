/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


/**
 * Default color of the grid on the map.
 */
static char const * DEFAULT_GRID_COLOR = "#0022ff";


GridLayer::GridLayer(Map * map, QObject * parent) : Layer{map, parent} {
    getAttributes()["color"] = DEFAULT_GRID_COLOR;
}


void GridLayer::draw(QPainter & painter, int tileSize) const {
    drawXAxis(painter, tileSize);
    drawYAxis(painter, tileSize);
    drawBorder(painter, tileSize);
}


void GridLayer::drawBorder(QPainter & painter, int tileSize) const {

    QSize size = getMap()->getCoordinateSystem()->getSize() * tileSize;

    painter.setPen(QPen(getColor(), 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawRect(0, 0, size.width(), size.height());

    auto nOuterTickLength = tileSize / 4;
    for (int x = 0; x <= size.width(); x += tileSize) {
        painter.drawLine(x, -nOuterTickLength, x, 0);
        painter.drawLine(x, size.height(), x, size.height() + nOuterTickLength);
    }
    for (int y = 0; y <= size.height(); y += tileSize) {
        painter.drawLine(-nOuterTickLength, y, 0, y);
        painter.drawLine(size.width(), y, size.width() + nOuterTickLength, y);
    }
}


void GridLayer::drawXAxis(QPainter & painter, int tileSize) const {

    QSize cSize = getMap()->getCoordinateSystem()->getSize() * tileSize;
    painter.setPen(QPen(getColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int x = tileSize; x <= cSize.width() - tileSize; x += tileSize) {
        painter.drawLine(x, 0, x, cSize.height());
    }
}


void GridLayer::drawYAxis(QPainter & painter, int tileSize) const {

    QSize cSize = getMap()->getCoordinateSystem()->getSize() * tileSize;
    painter.setPen(QPen(getColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int y = tileSize; y <= cSize.height() - tileSize; y += tileSize) {
        painter.drawLine(0, y, cSize.height(), y);
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
    getAttributes()["color"] = color.name(QColor::HexArgb);
}

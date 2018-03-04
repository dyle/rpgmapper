/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


static char const * DEFAULT_GRID_COLOR = "#0022ff";
static char const * WARNING_GRID_COLOR = "#ff0088";


GridLayer::GridLayer(Map * map, QObject * parent) : Layer{map, parent} {
    getAttributes()["gridColor"] = DEFAULT_GRID_COLOR;
}


void GridLayer::draw(QPainter & painter, int tileSize) const {
    drawXAxis(painter, tileSize);
    drawYAxis(painter, tileSize);
    drawBorder(painter, tileSize);
}


void GridLayer::drawBorder(QPainter & painter, int tileSize) const {

    QSize size = getMap()->getSize() * tileSize;

    painter.setPen(QPen(getGridColor(), 1, Qt::SolidLine, Qt::FlatCap));
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

    QSize cSize = getMap()->getSize() * tileSize;
    painter.setPen(QPen(getGridColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int x = tileSize; x <= cSize.width() - tileSize; x += tileSize) {
        painter.drawLine(x, 0, x, cSize.height());
    }
}


void GridLayer::drawYAxis(QPainter & painter, int tileSize) const {

    QSize cSize = getMap()->getSize() * tileSize;
    painter.setPen(QPen(getGridColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int y = tileSize; y <= cSize.height() - tileSize; y += tileSize) {
        painter.drawLine(0, y, cSize.height(), y);
    }
}


QColor GridLayer::getGridColor() const {

    auto iter = getAttributes().find("gridColor");
    if (iter != getAttributes().end()) {
        return QColor{(*iter).second};
    }

    return QColor{WARNING_GRID_COLOR};
}


void GridLayer::setGridColor(QColor color) {
    getAttributes()["gridColor"] = color.name(QColor::HexArgb);
}


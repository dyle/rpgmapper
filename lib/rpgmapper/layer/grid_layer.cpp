/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

static char const * DEFAULT_GRID_COLOR = "#0022ff";
static char const * WARNING_GRID_COLOR = "#ff0088";


GridLayer::GridLayer(Map * map, QObject * parent) : Layer{map, parent} {
    getAttributes()["color"] = DEFAULT_GRID_COLOR;
}


void GridLayer::draw(QPainter & painter, int tileSize) const {
    drawXAxis(painter, tileSize);
    drawYAxis(painter, tileSize);
    drawBorder(painter, tileSize);
}


void GridLayer::drawBorder(QPainter & painter, int tileSize) const {

    QSize size = getMap()->getSize() * tileSize;

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

    QSize cSize = getMap()->getSize() * tileSize;
    painter.setPen(QPen(getColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int x = tileSize; x <= cSize.width() - tileSize; x += tileSize) {
        painter.drawLine(x, 0, x, cSize.height());
    }
}


void GridLayer::drawYAxis(QPainter & painter, int tileSize) const {

    QSize cSize = getMap()->getSize() * tileSize;
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

    return QColor{WARNING_GRID_COLOR};
}


QJsonObject GridLayer::getJsonObject(rpgmapper::model::io::Content & content) const {
    QJsonObject jsonObject = Layer::getJsonObject(content);
    jsonObject["color"] = getColor().name(QColor::HexArgb);
    return jsonObject;
}


void GridLayer::setColor(QColor color) {
    getAttributes()["color"] = color.name(QColor::HexArgb);
}


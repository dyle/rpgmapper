/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


/**
 * The default color for the axis annotations.
 */
static char const * DEFAULT_AXIS_COLOR = "#000000";


AxisLayer::AxisLayer(Map * map, QObject * parent) : Layer{map, parent} {

    getAttributes()["color"] = DEFAULT_AXIS_COLOR;
    QFont cDefaultFont{"Monospace", 10};
    getAttributes()["font"] = cDefaultFont.toString();
}


void AxisLayer::draw(QPainter & painter, int tileSize) const {
    drawXAnnotation(painter, tileSize);
    drawYAnnotation(painter, tileSize);
}


void AxisLayer::drawXAnnotation(QPainter & painter, int tileSize) const {

    painter.setPen(getColor());
    painter.setFont(getFont());

    QSize cSize = getMap()->getCoordinateSystem()->getSize();
    int nBottom = cSize.height() * tileSize;

    for (int x = 0; x < cSize.width(); ++x) {

        auto mapPosition = getMap()->getCoordinateSystem()->transposeToMapCoordinates(x, 0);
        QString sX = getMap()->getCoordinateSystem()->tanslateToNumeralOnX(mapPosition.x());

        QRect cUpperRect{x * tileSize, -tileSize, tileSize, tileSize};
        painter.drawText(cUpperRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
        QRect cLowerRect{x * tileSize, nBottom, tileSize, tileSize};
        painter.drawText(cLowerRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
    }
}


void AxisLayer::drawYAnnotation(QPainter & painter, int tileSize) const {

    painter.setPen(getColor());
    painter.setFont(getFont());

    QSize cSize = getMap()->getCoordinateSystem()->getSize();
    int nRight = cSize.width() * tileSize;

    for (int y = 0; y < cSize.height(); ++y) {

        auto mapPosition = getMap()->getCoordinateSystem()->transposeToMapCoordinates(0, y);
        QString sY = getMap()->getCoordinateSystem()->tanslateToNumeralOnY(mapPosition.y());

        QRect cLeftRect{-tileSize, y * tileSize, tileSize, tileSize};
        painter.drawText(cLeftRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
        QRect cRightRect{nRight, y * tileSize, tileSize, tileSize};
        painter.drawText(cRightRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
    }
}


QColor AxisLayer::getColor() const {

    auto iter = getAttributes().find("color");
    if (iter != getAttributes().end()) {
        return QColor{(*iter).second};
    }
    return QColor{DEFAULT_AXIS_COLOR};
}


QFont AxisLayer::getFont() const {

    QFont res{"Monospace", 10};
    auto iter = getAttributes().find("font");
    if (iter != getAttributes().end()) {
        res.fromString((*iter).second);
    }
    return res;
}


QJsonObject AxisLayer::getJSON(rpgmapper::model::io::Content & content) const {
    QJsonObject jsonObject = Layer::getJSON(content);
    jsonObject["color"] = getColor().name(QColor::HexArgb);
    jsonObject["font"] = getFont().toString();
    return jsonObject;
}


void AxisLayer::setColor(QColor color) {
    getAttributes()["color"] = color.name(QColor::HexArgb);
}


void AxisLayer::setFont(QFont font) {
    getAttributes()["font"] = font.toString();
}

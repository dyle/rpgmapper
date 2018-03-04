/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


static char const * DEFAULT_AXIS_COLOR = "#000000";


AxisLayer::AxisLayer(Map * map, QObject * parent) : Layer{map, parent} {

    getAttributes()["axisColor"] = DEFAULT_AXIS_COLOR;
    QFont cDefaultFont{"Monospace", 10};
    getAttributes()["axisFont"] = cDefaultFont.toString();
}


void AxisLayer::draw(QPainter & painter, int tileSize) const {
    drawXAnnotation(painter, tileSize);
    drawYAnnotation(painter, tileSize);
}


void AxisLayer::drawXAnnotation(QPainter & painter, int tileSize) const {

    painter.setPen(getAxisFontColor());
    painter.setFont(getAxisFont());

    QSize cSize = getMap()->getSize();
    int nBottom = cSize.height() * tileSize;

    for (int x = 0; x < cSize.width(); ++x) {

        auto mapPosition = getMap()->getCoordinateSystem().transpose(x, 0);
        QString sX = getMap()->tanslateToNumeralOnX(mapPosition.x());

        QRect cUpperRect{x * tileSize, -tileSize, tileSize, tileSize};
        painter.drawText(cUpperRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
        QRect cLowerRect{x * tileSize, nBottom, tileSize, tileSize};
        painter.drawText(cLowerRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
    }
}


void AxisLayer::drawYAnnotation(QPainter & painter, int tileSize) const {

    painter.setPen(getAxisFontColor());
    painter.setFont(getAxisFont());

    QSize cSize = getMap()->getSize();
    int nRight = cSize.width() * tileSize;

    for (int y = 0; y < cSize.height(); ++y) {

        auto mapPosition = getMap()->getCoordinateSystem().transpose(0, y);
        QString sY = getMap()->tanslateToNumeralOnY(mapPosition.y());

        QRect cLeftRect{-tileSize, y * tileSize, tileSize, tileSize};
        painter.drawText(cLeftRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
        QRect cRightRect{nRight, y * tileSize, tileSize, tileSize};
        painter.drawText(cRightRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
    }
}


QFont AxisLayer::getAxisFont() const {

    QFont res{"Monospace", 10};
    auto iter = getAttributes().find("axisFont");
    if (iter != getAttributes().end()) {
        res.fromString((*iter).second);
    }
    return res;
}


QColor AxisLayer::getAxisFontColor() const {

    auto iter = getAttributes().find("axisColor");
    if (iter != getAttributes().end()) {
        return QColor{(*iter).second};
    }
    return QColor{DEFAULT_AXIS_COLOR};
}


void AxisLayer::setAxisFont(QFont font) {
    getAttributes()["axisFont"] = font.toString();
}


void AxisLayer::setAxisColor(QColor color) {
    getAttributes()["axisColor"] = color.name(QColor::HexArgb);
}

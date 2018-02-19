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
    getAttributes()["color"] = DEFAULT_GRID_COLOR;
    QFont cDefaultFont{"Monospace", 10};
    getAttributes()["font"] = cDefaultFont.toString();
    getAttributes()["image"] = "";
}


void GridLayer::draw(QPainter & painter, int tileSize) const {
    drawXAxis(painter, tileSize);
    drawYAxis(painter, tileSize);
    drawBorder(painter, tileSize);
    drawXAnnotation(painter, tileSize);
    drawYAnnotation(painter, tileSize);
}


void GridLayer::drawBorder(QPainter & painter, int tileSize) const {

    QSize size = getMap()->getSize() * tileSize;

    painter.setPen(QPen(gridColor(), 1, Qt::SolidLine, Qt::FlatCap));
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


void GridLayer::drawXAnnotation(QPainter & painter, int tileSize) const {

    painter.setPen(gridColor());
    painter.setFont(gridFont());

    QSize cSize = getMap()->getSize();
    int nBottom = cSize.height() * tileSize;

    for (int x = 0; x < cSize.width(); ++x) {

        QString sX = getMap()->tanslateToNumeralOnX(x);

        QRect cUpperRect{x * tileSize, -tileSize, tileSize, tileSize};
        painter.drawText(cUpperRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
        QRect cLowerRect{x * tileSize, nBottom, tileSize, tileSize};
        painter.drawText(cLowerRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
    }
}


void GridLayer::drawXAxis(QPainter & painter, int tileSize) const {

    QSize cSize = getMap()->getSize() * tileSize;
    painter.setPen(QPen(gridColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int x = tileSize; x <= cSize.width() - tileSize; x += tileSize) {
        painter.drawLine(x, 0, x, cSize.height());
    }
}


void GridLayer::drawYAnnotation(QPainter & painter, int tileSize) const {

    painter.setPen(gridColor());
    painter.setFont(gridFont());

    QSize cSize = getMap()->getSize();
    int nRight = cSize.width() * tileSize;

    for (int y = 0; y < cSize.height(); ++y) {

        QString sY = getMap()->tanslateToNumeralOnY(y);

        QRect cLeftRect{-tileSize, y * tileSize, tileSize, tileSize};
        painter.drawText(cLeftRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
        QRect cRightRect{nRight, y * tileSize, tileSize, tileSize};
        painter.drawText(cRightRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
    }
}


void GridLayer::drawYAxis(QPainter & painter, int tileSize) const {

    QSize cSize = getMap()->getSize() * tileSize;
    painter.setPen(QPen(gridColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int y = tileSize; y <= cSize.height() - tileSize; y += tileSize) {
        painter.drawLine(0, y, cSize.height(), y);
    }
}


QColor GridLayer::gridColor() const {

    auto iter = getAttributes().find("color");
    if (iter != getAttributes().end()) {
        return QColor{(*iter).second};
    }

    return QColor{WARNING_GRID_COLOR};
}


QFont GridLayer::gridFont() const {

    QFont res{"Monospace", 10};

    auto iter = getAttributes().find("font");
    if (iter != getAttributes().end()) {
        res.fromString((*iter).second);
    }

    return res;
}

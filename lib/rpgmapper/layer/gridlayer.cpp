/*
 * grid.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// ------------------------------------------------------------
// defs


#define DEFAULT_GRID_COLOR        "#f0f0ff"
#define WARNING_GRID_COLOR        "#ff0088"


// ------------------------------------------------------------
// incs

#include <QPainter>

// rpgmapper
#include <rpgmapper/map.hpp>
#include "gridlayer.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cMap        parent object
 * @param   nId         id of the layer
 * @param   eLayer      the layer type
 */
GridLayer::GridLayer(Map * cMap, layerid_t nId) : Layer(cMap, nId, Layer::layer_t::grid) {

    attributes()["color"] = DEFAULT_GRID_COLOR;

    QFont cDefaultFont{"Monospace", 10};
    attributes()["font"] = cDefaultFont.toString();
}


/**
 * Draw the border around the map.
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::drawBorder(QPainter & cPainter, int nTileSize) const {

    QSize cSize = map()->size() * nTileSize;

    cPainter.setPen(QPen(gridColor(), 1, Qt::SolidLine, Qt::FlatCap));
    cPainter.drawRect(0, 0, cSize.width(), cSize.height());

    auto nOuterTickLength = nTileSize / 4;
    for (int x = 0; x <= cSize.width(); x += nTileSize) {
        cPainter.drawLine(x, -nOuterTickLength, x, 0);
        cPainter.drawLine(x, cSize.height(), x, cSize.height() + nOuterTickLength);
    }
    for (int y = 0; y <= cSize.height(); y += nTileSize) {
        cPainter.drawLine(-nOuterTickLength, y, 0, y);
        cPainter.drawLine(cSize.width(), y, cSize.width() + nOuterTickLength, y);
    }
}


/**
 * Draw the current layer given the painter.
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::drawLayer(QPainter & cPainter, int nTileSize) const {
    drawXAxis(cPainter, nTileSize);
    drawYAxis(cPainter, nTileSize);
    drawBorder(cPainter, nTileSize);
    drawXAnnotation(cPainter, nTileSize);
    drawYAnnotation(cPainter, nTileSize);
}


/**
 * Draw X-axis annotation
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::drawXAnnotation(QPainter & cPainter, int nTileSize) const {

    cPainter.setPen(gridColor());
    cPainter.setFont(gridFont());

    QSize cSize = map()->size();
    int nBottom = cSize.height() * nTileSize;

    for (int x = 0; x < cSize.width(); ++x) {

        QString sX = map()->translateX(x);

        QRect cUpperRect{x * nTileSize, -nTileSize, nTileSize, nTileSize};
        cPainter.drawText(cUpperRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
        QRect cLowerRect{x * nTileSize, nBottom, nTileSize, nTileSize};
        cPainter.drawText(cLowerRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sX);
    }
}


/**
 * Draw X-axis ticks
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::drawXAxis(QPainter & cPainter, int nTileSize) const {

    QSize cSize = map()->size() * nTileSize;
    cPainter.setPen(QPen(gridColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int x = nTileSize; x <= cSize.width() - nTileSize; x += nTileSize) {
        cPainter.drawLine(x, 0, x, cSize.height());
    }
}


/**
 * Draw Y-axis annotation
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::drawYAnnotation(QPainter & cPainter, int nTileSize) const {

    cPainter.setPen(gridColor());
    cPainter.setFont(gridFont());

    QSize cSize = map()->size();
    int nRight = cSize.width() * nTileSize;

    for (int y = 0; y < cSize.height(); ++y) {

        QString sY = map()->translateY(y);

        QRect cLeftRect{-nTileSize, y * nTileSize, nTileSize, nTileSize};
        cPainter.drawText(cLeftRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
        QRect cRightRect{nRight, y * nTileSize, nTileSize, nTileSize};
        cPainter.drawText(cRightRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, sY);
    }
}


/**
 * Draw Y-axis ticks
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::drawYAxis(QPainter & cPainter, int nTileSize) const {

    QSize cSize = map()->size() * nTileSize;
    cPainter.setPen(QPen(gridColor(), 1, Qt::DotLine, Qt::FlatCap));
    for (int y = nTileSize; y <= cSize.height() - nTileSize; y += nTileSize) {
        cPainter.drawLine(0, y, cSize.height(), y);
    }
}


/**
 * Retrieve the grid color.
 *
 * @return  the color encoded in the tiles of this layer
 */
QColor GridLayer::gridColor() const {

    auto iter = attributes().find("color");
    if (iter != attributes().end()) {
        return QColor{(*iter).second};
    }

    return QColor{WARNING_GRID_COLOR};
}


/**
 * Retrieve the grid font for X Axis.
 *
 * @return  the font used for the grid
 */
QFont GridLayer::gridFont() const {

    QFont res{"Monospace", 10};

    auto iter = attributes().find("font");
    if (iter != attributes().end()) {
        res.fromString((*iter).second);
    }

    return res;
}

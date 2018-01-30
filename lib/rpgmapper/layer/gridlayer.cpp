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

    addTile(0,  Tile{{"color", DEFAULT_GRID_COLOR}, {"font", QFont().toString()}});
}


/**
 * Retrieve the grid color.
 *
 * @return  the color encoded in the tiles of this layer
 */
QColor GridLayer::gridColor() const {

    if (!fields().empty()) {
        auto const & cTile = fields().at(0).cTiles[0];
        auto iter = cTile.find("color");
        if (iter != cTile.end()) {
            return QColor{(*iter).second};
        }
    }

    return QColor{WARNING_GRID_COLOR};
}


/**
 * Draw the current layer given the painter.
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void GridLayer::draw(QPainter & cPainter, int nTileSize) const {

    QSize cSize = map()->size() * nTileSize;
    QColor cGridColor = gridColor();

    cPainter.setPen(cGridColor);
    cPainter.drawRect(QRect{-nTileSize, -nTileSize, cSize.width() + nTileSize, cSize.height() + nTileSize});
}

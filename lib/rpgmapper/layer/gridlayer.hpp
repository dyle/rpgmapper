/*
 * grid.hpp
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


#ifndef MODEL_LAYER_GRID_HPP
#define MODEL_LAYER_GRID_HPP


// ------------------------------------------------------------
// incs

// rpgmapper
#include <rpgmapper/layer.hpp>
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A layer on a map.
 */
class GridLayer : public Layer {


Q_OBJECT


public:


    /**
     * Ctor.
     *
     * @param   cMap        parent object
     * @param   nId         id of the layer
     */
    explicit GridLayer(Map * cMap, layerid_t nId);


private:


    /**
     * Draw the border around the map.
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawBorder(QPainter & cPainter, int nTileSize) const;


    /**
     * Draw the current layer given the painter.
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawLayer(QPainter & cPainter, int nTileSize) const override;


    /**
     * Draw X-axis ticks
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawXAxis(QPainter & cPainter, int nTileSize) const;


    /**
     * Draw Y-axis ticks
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawYAxis(QPainter & cPainter, int nTileSize) const;


    /**
     * Retrieve the grid color.
     *
     * @return  the color encoded in the tiles of this layer
     */
    QColor gridColor() const;

};


}
}


#endif

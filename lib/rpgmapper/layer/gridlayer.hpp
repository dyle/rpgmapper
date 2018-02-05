/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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
     * Draw X-axis annotation
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawXAnnotation(QPainter & cPainter, int nTileSize) const;


    /**
     * Draw X-axis ticks
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawXAxis(QPainter & cPainter, int nTileSize) const;


    /**
     * Draw Y-axis annotation
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawYAnnotation(QPainter & cPainter, int nTileSize) const;


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


    /**
     * Retrieve the grid font for X Axis.
     *
     * @return  the font used for the grid
     */
    QFont gridFont() const;

};


}
}


#endif

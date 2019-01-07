/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_GRID_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_GRID_LAYER_HPP

#include <QColor>
#include <QJsonObject>
#include <QPainter>

#include <rpgmapper/layer/layer.hpp>


// fwd
namespace rpgmapper::model { class Map; }


namespace rpgmapper::model::layer {


/**
 * Objects of the GridLayer class draw grids on a map.
 */
class GridLayer : public Layer {

    Q_OBJECT

public:

    /**
     * Constructs a new GridLayer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit GridLayer(rpgmapper::model::Map * map);

    /**
     * Destructs the GridLayer.
     */
    ~GridLayer() override = default;

    /**
     * Draws the grid onto the map.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void draw(QPainter & painter, int tileSize) const override;

    /**
     * Gets the color of the grid.
     *
     * @return  the color used to paint the grid on the map.
     */
    QColor getColor() const;

    /**
     * Extracts this layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;

    /**
     * Applies a new grid color.
     *
     * @param   color   the new grid color.
     */
    void setColor(QColor color);

signals:
    
    /**
     * The grid color has changed.
     *
     * @param   color       the new grid color.
     */
    void gridColorChanged(QColor color);
    
private:

    /**
     * Draws the map border.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawBorder(QPainter & painter, int tileSize) const;

    /**
     * Draws all X-axis.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawXAxis(QPainter & painter, int tileSize) const;

    /**
     * Draws all Y-axis.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawYAxis(QPainter & painter, int tileSize) const;

};


}


#endif

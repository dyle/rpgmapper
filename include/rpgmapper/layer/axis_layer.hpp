/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_AXIS_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_AXIS_LAYER_HPP

#include <QColor>
#include <QFont>

#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {
namespace layer {


/**
 * An AxisLayer is responsible for holding and drawing the axis information on a map.
 *
 * This layers knows how the X- and the Y-coordinates on a map are labeled.
 */
class AxisLayer : public Layer {

    Q_OBJECT

public:

    /**
     * Constructs a new AxisLayer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit AxisLayer(Map * map);

    /**
     * Destructs the AxisLayer.
     */
    ~AxisLayer() override = default;

    /**
     * Draws the axis information (e.g. major and minor ticks, indizes, ...).
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void draw(QPainter & painter, int tileSize) const override;

    /**
     * Returns the color used for drawing the axis lines and annotations.
     *
     * @return  the color used for the axis lines and annotations.
     */
    QColor getColor() const;

    /**
     * Gets the font used for drawing the annotations.
     *
     * @return  the font used for drawing the annotations.
     */
    QFont getFont() const;

    /**
     * Extracts this layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;

    /**
     * Applies a new color to the axis lines and annotations.
     *
     * @param   color   the new color for the axis lines and annotations.
     */
    void setColor(QColor color);

    /**
     * Sets a new font used for the annotations.
     *
     * @param   font    the new font for the annotations.
     */
    void setFont(QFont font);

signals:
    
    /**
     * The color or the axis has changed.
     *
     * @param   color       the new axis color.
     */
    void axisColorChanged(QColor color);
    
    /**
     * The font of the axis has changed.
     *
     * @param   font        the new axis font.
     */
    void axisFontChanged(QFont font);
    
private:

    /**
     * Draws the X annotations.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawXAnnotation(QPainter & painter, int tileSize) const;

    /**
     * Draws the Y annotations.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawYAnnotation(QPainter & painter, int tileSize) const;
};


}
}
}


#endif

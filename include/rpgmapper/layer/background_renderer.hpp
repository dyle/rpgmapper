/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_BACKGROUND_RENDERER_HPP
#define RPGMAPPER_MODEL_LAYER_BACKGROUND_RENDERER_HPP

#include <QPainter>
#include <QPixmap>
#include <QRect>

#include <rpgmapper/layer/image_render_mode.hpp>


namespace rpgmapper::model::layer {


/**
 * This class is responsible for rendering the background of a map.
 */
class BackgroundRenderer {

    /**
     * The current render mode: how the background is multiplied across the maps background.
     */
    ImageRenderMode renderMode = ImageRenderMode::plain;

public:

    /**
     * Constructor.
     */
    BackgroundRenderer() = default;

    /**
     * Returns the current render mode.
     *
     * @return  the current render mode.
     */
    rpgmapper::model::layer::ImageRenderMode getImageRenderMode() const {
        return renderMode;
    }

    /**
     * Returns the pixmap (image) which is drawn on the map background.
     *
     * @return  the QPixmap to draw on the map.
     */
    virtual QPixmap const * getBackgroundPixmap() const = 0;

    /**
     * Applies a new render mode to the background drawer.
     *
     * @param   renderMode  the new mode specifying how to draw the map background.
     */
    virtual void setImageRenderMode(rpgmapper::model::layer::ImageRenderMode renderMode) {
        this->renderMode = renderMode;
    }

protected:

    /**
     * Draws the maps background
     *
     * @param   painter     QPainter used for drawing.
     * @param   rect        area to draw.
     */
    void drawBackground(QPainter & painter, QRect const & rect) const;

private:

    /**
     * Draws a plain background image.
     *
     * @param   painter     QPainter used for drawing.
     * @param   rect        area to draw.
     */
    void drawPlainBackground(QPainter & painter, QRect const & rect) const;
    
    /**
     * Scales the background image to fit the maps dimensions.
     *
     * @param   painter     QPainter used for drawing.
     * @param   rect        area to draw.
     */
    void drawScaledBackground(QPainter & painter, QRect const & rect) const;
    
    /**
     * Repeats drawing of the background image over and over.
     *
     * @param   painter     QPainter used for drawing.
     * @param   rect        area to draw.
     */
    void drawTiledBackground(QPainter & painter, QRect const & rect) const;
};


}


#endif

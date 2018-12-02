/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_BACKGROUND_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_BACKGROUND_LAYER_HPP

#include <QColor>
#include <QMargins>
#include <QPixmap>
#include <QRect>
#include <QString>

#include <rpgmapper/layer/background_renderer.hpp>
#include <rpgmapper/layer/image_render_mode.hpp>
#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/resource_pointer.hpp>


namespace rpgmapper {
namespace model {


/**
 * The BackgroundLayer class is responsible to draw the maps background.
 */
class BackgroundLayer : public Layer, public BackgroundRenderer {

    Q_OBJECT
    
    QPixmap * backgroundPixmap;            /**< Pixmap used to draw the background. */

public:

    /**
     * Constructs a new BackgroundLayer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit BackgroundLayer(Map * map);

    /**
     * Destructs the BackgroundLayer.
     */
    ~BackgroundLayer() override;

    /**
     * Extract the layer information in the given JSON object and apply it to this layer.
     *
     * @param   json        The JSON object which maybe hold some information.
     * @return  always true (TODO: why? kick this! Unnecessary)
     */
    bool applyJSON(QJsonObject const & json) override;

    /**
     * Draws the background of the map.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void draw(QPainter & painter, int tileSize) const override;
    
    /**
     * Returns the pixmap (image) which is drawn on the map background.
     *
     * @return  the QPixmap to draw on the map.
     */
    QPixmap const * getBackgroundPixmap() const override;
    
    /**
     * Gets the color of the background.
     *
     * @return  the color used to fill a map's background.
     */
    QColor getColor() const;

    /**
     * Gets the resource name used to draw the background.
     *
     * @return  the resource name used to draw the background.
     */
    QString getImageResource() const;
    
    /**
     * Extracts this layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;

    /**
     * Gets the image rendering mode setting as string.
     *
     * @return  the image rendering mode settings as string.
     */
    QString getRendering() const;

    /**
     * Checks if the layer "only" applies a solid color as background.
     *
     * @return  true, if the background is just a color.
     */
    bool isColorRendered() const;

    /**
     * Checks if the background uses an image.
     *
     * @return  true, if an image is rendered as background.
     */
    bool isImageRendered() const;

    /**
     * Checks if the image should rendered plain.
     *
     * @return  true, if the image should be draw 1:1 as-is.
     */
    bool isImageRenderedPlain() const {
        return getImageRenderMode() == ImageRenderMode::plain;
    }

    /**
     * Checks if the image should be scaled according to the map size.
     *
     * @return  true, if the image should be stretched or squeezed to fit the map.
     */
    bool isImageRenderedScaled() const {
        return getImageRenderMode() == ImageRenderMode::scaled;
    }

    /**
     * Checks if the image should be repeatedly be drawn 1:1 on the map.
     *
     * @return  true, if the image should be repeatedly be drawn on the map.
     */
    bool isImageRenderedTiled() const {
        return getImageRenderMode() == ImageRenderMode::tiled;
    }

    /**
     * Checks, if the given string represnts a valid rendering setting ("color" or "string").
     *
     * @param   a string value indicating the rendering style of the background.
     * @return  true, if this is indeed a known rendering style.
     */
    static bool isValidRendering(QString rendering);

    /**
     * Applies a new background color.
     *
     * @param   color   the new background color.
     */
    void setColor(QColor color);

    /**
     * Sets a new image background rendering mode.
     *
     * @param   mode    the new background image rendering style.
     */
    void setImageRenderMode(ImageRenderMode mode) override;
    
    /**
     * Applies a new name for the background image resource.
     *
     * @param    name       the name of the new image resource.
     */
    void setImageResource(QString name);
    
    /**
     * Sets a new rendering theme: "color" or "image".
     *
     * @param   rendering       either "color" or "image".
     */
    void setRendering(QString rendering);

signals:
    
    /**
     * The background color has changed.
     *
     * @param   color       the new background color.
     */
    void backgroundColorChanged(QColor color);
    
    /**
     * The background image changed.
     *
     * @param   name        the new background image.
     */
    void backgroundImageChanged(QString name);
    
    /**
     * The background image render mode changed.
     *
     * @param   mode        the new background image render mode.
     */
    void backgroundImageRenderModeChanged(ImageRenderMode mode);
    
    /**
     * The background rendering has changed.
     *
     * @param   rendering   the new background rendering.
     */
    void backgroundRenderingChanged(QString rendering);
    
private:

    /**
     * Draws the background of the map with a solid color
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawColor(QPainter & painter, int tileSize) const;
    
    /**
     * Draws the background of the map with an image.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void drawImage(QPainter & painter, int tileSize) const;
};


}
}


#endif

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_BACKGROUND_RENDERER_HPP
#define RPGMAPPER_MODEL_BACKGROUND_RENDERER_HPP


#include <QPainter>
#include <QPixmap>

#include <rpgmapper/layer/background_layer.hpp>
#include <rpgmapper/layer/image_render_mode.hpp>


namespace rpgmapper {
namespace model {


class BackgroundRenderer {

    rpgmapper::model::ImageRenderMode renderMode = rpgmapper::model::ImageRenderMode::plain;

public:

    BackgroundRenderer() = default;

    rpgmapper::model::ImageRenderMode getImageRenderMode() const { return renderMode; }

    virtual QPixmap const * getBackgroundPixmap() const = 0;

    void setImageRenderMode(rpgmapper::model::ImageRenderMode renderMode) {
        this->renderMode = renderMode;
    }

protected:

    void drawBackground(QPainter & painter, QRect const & rect);

private:

    void drawPlainBackground(QPainter & painter, QRect const & rect);

    void drawScaledBackground(QPainter & painter, QRect const & rect);

    void drawTiledBackground(QPainter & painter, QRect const & rect);
};


}
}


#endif

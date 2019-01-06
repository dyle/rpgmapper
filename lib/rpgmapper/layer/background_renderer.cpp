/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/background_renderer.hpp>

using namespace rpgmapper::model::layer;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


void BackgroundRenderer::drawBackground(QPainter & painter, QRect const & rect) const {

    auto * const pixmap = getBackgroundPixmap();
    if ((pixmap == nullptr) || (pixmap->isNull())) {
        return;
    }

    switch (getImageRenderMode()) {

        case ImageRenderMode::plain:
            drawPlainBackground(painter, rect);
            break;

        case ImageRenderMode::scaled:
            drawScaledBackground(painter, rect);
            break;

        case ImageRenderMode::tiled:
            drawTiledBackground(painter, rect);
            break;
    }
}


void BackgroundRenderer::drawPlainBackground(QPainter & painter, UNUSED QRect const & rect) const {
    painter.drawPixmap(0, 0, *getBackgroundPixmap());
}


void BackgroundRenderer::drawScaledBackground(QPainter & painter, QRect const & rect) const {
    painter.drawPixmap(rect, *getBackgroundPixmap());
}


void BackgroundRenderer::drawTiledBackground(QPainter & painter, QRect const & rect) const {
    painter.drawTiledPixmap(rect, *getBackgroundPixmap());
}

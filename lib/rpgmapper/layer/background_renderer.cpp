/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/background_renderer.hpp>

using namespace rpgmapper::model;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


void BackgroundRenderer::drawBackground(QPainter & painter, QRect const & rect) {

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


void BackgroundRenderer::drawPlainBackground(QPainter & painter, UNUSED QRect const & rect) {
    painter.drawPixmap(0, 0, *getBackgroundPixmap());
}


void BackgroundRenderer::drawScaledBackground(QPainter & painter, QRect const & rect) {
    painter.drawPixmap(rect, *getBackgroundPixmap());
}


void BackgroundRenderer::drawTiledBackground(QPainter & painter, QRect const & rect) {
    painter.drawTiledPixmap(rect, *getBackgroundPixmap());
}

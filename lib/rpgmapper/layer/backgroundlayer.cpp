/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#define DEFAULT_BACKGROUND_COLOR        "#000060"
#define WARNING_BACKGROUND_COLOR        "#ff0088"


// ------------------------------------------------------------
// incs

#include <QPainter>

// rpgmapper
#include <rpgmapper/map.hpp>
#include "backgroundlayer.hpp"

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
BackgroundLayer::BackgroundLayer(Map * cMap, layerid_t nId) : Layer(cMap, nId, Layer::layer_t::background) {
    attributes()["color"] = DEFAULT_BACKGROUND_COLOR;
}


/**
 * Retrieve the background color.
 *
 * @return  the color encoded in the tiles of this layer
 */
QColor BackgroundLayer::backgroundColor() const {

    auto iter = attributes().find("color");
    if (iter != attributes().end()) {
        return QColor{(*iter).second};
    }

    return QColor{WARNING_BACKGROUND_COLOR};
}


/**
 * Draw the current layer given the painter.
 *
 * @param   cPainter        painter instance to draw this layer
 * @param   nTileSize       dimension of a single tile
 */
void BackgroundLayer::drawLayer(QPainter & cPainter, int nTileSize) const {

    QSize cSize = map()->size() * nTileSize;
    QColor cBackgroundColor = backgroundColor();
    cPainter.fillRect(QRect{QPoint{0, 0}, cSize}, cBackgroundColor);
}

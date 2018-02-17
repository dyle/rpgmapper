/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QColor>

#include <rpgmapper/layer/background_layer.hpp>

using namespace rpgmapper::model;


static char const * BACKGROUND_COLOR_DEFAULT = "#000060";


BackgroundLayer::BackgroundLayer(Map * map, QObject * parent) : Layer{map, parent} {
    getAttributes()["color"] = BACKGROUND_COLOR_DEFAULT;
}


QColor BackgroundLayer::getColor() const {
    auto pair = getAttributes().find("color");
    if (pair == getAttributes().end()) {
        return QColor{QString{BACKGROUND_COLOR_DEFAULT}};
    }
    return QColor{pair->second};
}





#if 0

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


#endif
/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QColor>

#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


static char const * BACKGROUND_COLOR_DEFAULT = "#fafaff";


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


void BackgroundLayer::draw(QPainter & painter, int tileSize) const {
    QSize size = getMap()->getSize() * tileSize;
    QColor backgroundColor = getColor();
    painter.fillRect(QRect{QPoint{0, 0}, size}, backgroundColor);

}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QPainter>

#include <rpgmapper/tile.hpp>

#include "currenttilewidget.hpp"

using namespace rpgmapper::view;


CurrentTileWidget::CurrentTileWidget(QWidget * parent) : QWidget{parent} {
}


void CurrentTileWidget::paintEvent(QPaintEvent * event) {
    
    QWidget::paintEvent(event);
    if (!currentTile) {
        return;
    }
    
    QPainter painter{this};
    
    static int tileSize = 48;
    QRect rect{0, 0, tileSize, tileSize};
    currentTile->draw(painter, tileSize);
}

void CurrentTileWidget::setCurrentTile(rpgmapper::model::TilePointer tile) {
    currentTile = tile;
    update();
}

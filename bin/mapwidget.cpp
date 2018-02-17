/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#define STANDARD_TILE_SIZE      48

#include <QMouseEvent>
#include <QPainter>

#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/map.hpp>
#include "mapwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


MapWidget::MapWidget(QWidget * parent) : QWidget{parent} {
    setMouseTracking(true);
}


void MapWidget::mapChanged() {
    QSize cSize{(map->getSize().width() + 2) * STANDARD_TILE_SIZE,
                (map->getSize().height() + 2) * STANDARD_TILE_SIZE};
    resize(cSize);
}


void MapWidget::mouseMoveEvent(QMouseEvent * event) {
    QWidget::mouseMoveEvent(event);
    int x = event->pos().x() / STANDARD_TILE_SIZE - 1;
    int y = event->pos().y() / STANDARD_TILE_SIZE - 1;
    emit hoverCoordinates(x, y);
}


void MapWidget::paintEvent(QPaintEvent * event) {

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setTransform(QTransform::fromTranslate(STANDARD_TILE_SIZE, STANDARD_TILE_SIZE));
    painter.setViewTransformEnabled(true);

//    for (auto const & cPair : map->layers()) {
//        cPair.second->draw(painter, STANDARD_TILE_SIZE);
//    }
}


void MapWidget::setMap(rpgmapper::model::MapPointer & map) {
    this->map = map;
//    connect(map.data(), &Map::changedSize, this, &MapWidget::mapChanged);
    update();
}

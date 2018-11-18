/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QMouseEvent>
#include <QPainter>

#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

#include "mapwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


#define STANDARD_TILE_SIZE      48


MapWidget::MapWidget(QWidget * parent) : QWidget{parent} {
    setMouseTracking(true);
}


void MapWidget::mapSizeChanged(QSize size) {
    resize(QSize{(size.width() + 2) * STANDARD_TILE_SIZE, (size.height() + 2) * STANDARD_TILE_SIZE});
}


void MapWidget::mouseMoveEvent(QMouseEvent * event) {

    QWidget::mouseMoveEvent(event);
    int x = event->pos().x() / STANDARD_TILE_SIZE - 1;
    int y = event->pos().y() / STANDARD_TILE_SIZE - 1;
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }
    auto coordinateSystem = map->getCoordinateSystem();

    auto size = coordinateSystem->getSize();
    if ((x >= 0) && (x < size.width()) && (y >= 0) && (y < size.height())) {
        auto mapPosition = map->getCoordinateSystem()->transposeToMapCoordinates(x, y);
        emit hoverCoordinates(static_cast<int>(mapPosition.x()), static_cast<int>(mapPosition.y()));
    }
}


void MapWidget::paintEvent(QPaintEvent * event) {

    auto start = std::chrono::system_clock::now();

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setTransform(QTransform::fromTranslate(STANDARD_TILE_SIZE, STANDARD_TILE_SIZE));
    painter.setViewTransformEnabled(true);
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }

    for (auto layer : map->getLayers().collectVisibleLayers()) {
        layer->draw(painter, STANDARD_TILE_SIZE);
    }

    auto end = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    averagePaintDuration << milliseconds;
}


void MapWidget::setMap(QString mapName) {
    
    if (this->mapName == mapName) {
        return;
    }
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }
    this->mapName = mapName;
    auto coordinateSystem = map->getCoordinateSystem();
    
    connect(coordinateSystem.data(), &CoordinateSystem::sizeChanged, this, &MapWidget::mapSizeChanged);
}

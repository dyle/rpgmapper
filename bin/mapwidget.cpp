/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QMouseEvent>
#include <QPainter>

#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/map.hpp>
#include "mapwidget.hpp"

#define STANDARD_TILE_SIZE      48

using namespace rpgmapper::model;
using namespace rpgmapper::view;


MapWidget::MapWidget(QWidget * parent) : QWidget{parent} {
    setMouseTracking(true);
}


void MapWidget::mapChanged() {

    auto map = this->map.toStrongRef();
    if (map.data() == nullptr) {
        throw std::runtime_error("map of MapWidget no longer valid (nullptr).");
    }

    QSize size{(map->getSize().width() + 2) * STANDARD_TILE_SIZE, (map->getSize().height() + 2) * STANDARD_TILE_SIZE};
    resize(size);
}


void MapWidget::mouseMoveEvent(QMouseEvent * event) {

    QWidget::mouseMoveEvent(event);
    int x = event->pos().x() / STANDARD_TILE_SIZE - 1;
    int y = event->pos().y() / STANDARD_TILE_SIZE - 1;

    auto map = this->map.toStrongRef();
    if (map.data() == nullptr) {
        throw std::runtime_error("map of MapWidget no longer valid (nullptr).");
    }

    auto size = map->getSize();
    if ((x >= 0) && (x < size.width()) && (y >= 0) && (y < size.height())) {
        auto mapPosition = map->getCoordinateSystem().transposeToMapCoordinates(x, y);
        emit hoverCoordinates(mapPosition.x(), mapPosition.y());
    }
}


void MapWidget::paintEvent(QPaintEvent * event) {

    auto start = std::chrono::system_clock::now();

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setTransform(QTransform::fromTranslate(STANDARD_TILE_SIZE, STANDARD_TILE_SIZE));
    painter.setViewTransformEnabled(true);

    auto map = this->map.toStrongRef();
    if (map.data() == nullptr) {
        throw std::runtime_error("map of MapWidget no longer valid (nullptr).");
    }

    for (auto layer : map->collectVisibleLayers()) {
        layer->draw(painter, STANDARD_TILE_SIZE);
    }

    auto end = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    averagePaintDuration << milliseconds;
}


void MapWidget::setMap(rpgmapper::model::MapPointer & map) {
    this->map = map;
    connect(map.data(), &Map::changed, this, &MapWidget::update);
    connect(map.data(), &Map::resized, this, &MapWidget::mapChanged);
    mapChanged();
    update();
}


void MapWidget::update() {
    QWidget::update();
}

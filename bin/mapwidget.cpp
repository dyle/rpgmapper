#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QMouseEvent>

#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

#include "mapwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::model::layer;
using namespace rpgmapper::view;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

#define STANDARD_TILE_SIZE      48


MapWidget::MapWidget(QWidget * parent)
        : QWidget{parent},
          tileSize{STANDARD_TILE_SIZE},
          axisVisible{true},
          gridVisible{true},
          hoveredTilePosition{-1, -1} {
    setMouseTracking(true);
}


void MapWidget::applyCurrentSelectedTile() {

    auto session = Session::getCurrentSession();
    auto tile = session->getCurrentTile();
    if (!tile) {
        return;
    }
    
    auto map = session->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }
    
    if (map->place(static_cast<float>(hoveredTilePosition.x()), static_cast<float>(hoveredTilePosition.y()), tile)) {
        update();
    }
}


std::list<Layer const *> MapWidget::collectVisibleLayers() const {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }

    auto const & layerStack = map->getLayers();
    
    std::list<Layer const *> layers;
    
    layers.push_back(layerStack.getBackgroundLayer().data());
    
    for (auto & baseLayer : layerStack.getBaseLayers()) {
        layers.push_back(baseLayer.data());
    }
    
    if (isGridVisible()) {
        layers.push_back(layerStack.getGridLayer().data());
    }
    
    if (isAxisVisible()) {
        layers.push_back(layerStack.getAxisLayer().data());
    }
    
    for (auto & tileLayer : layerStack.getTileLayers()) {
        layers.push_back(tileLayer.data());
    }
    layers.push_back(layerStack.getTextLayer().data());
    
    return layers;
}


void MapWidget::drawHoveredTile(QPainter & painter) {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        return;
    }
    
    auto coordinateSystem = map->getCoordinateSystem();
    auto mapSize = coordinateSystem->getSize();
    auto mapRect = QRectF{0, 0, static_cast<float>(mapSize.width()), static_cast<float>(mapSize.height())};
    if (mapRect.contains(hoveredTilePosition.x(), hoveredTilePosition.y())) {
        
        int tileSize = getTileSize();
        QRect rect{static_cast<int>(hoveredTilePosition.x()) * tileSize,
                   static_cast<int>(hoveredTilePosition.y()) * tileSize,
                   tileSize,
                   tileSize};
        auto innerRect = coordinateSystem->getInnerRect(tileSize);
        rect.adjust(innerRect.x(), innerRect.y(), innerRect.x(), innerRect.y());
        
        QPalette systemPalette;
        painter.setPen(systemPalette.color(QPalette::Highlight));
        painter.drawRect(rect);
    }
}


void MapWidget::mapNameChanged(UNUSED QString oldName, QString newName) {
    mapName = std::move(newName);
}


void MapWidget::mapSizeChanged() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }
    
    auto rect = map->getCoordinateSystem()->getOuterRect(getTileSize());
    resize(rect.size());
}


void MapWidget::mouseMoveEvent(QMouseEvent * event) {

    QWidget::mouseMoveEvent(event);
    
    auto pointInfo = widgetToMapCoordinates(event->x(), event->y());
    if (std::get<1>(pointInfo)) {
        
        auto mapPosition = std::get<0>(pointInfo);
        auto newHoveredTilePosition = QPointF{mapPosition.x(), mapPosition.y()};
        if (newHoveredTilePosition != hoveredTilePosition) {
            
            hoveredTilePosition = newHoveredTilePosition;
            if (leftMouseButtonDown) {
                applyCurrentSelectedTile();
            }
            
            update();
            emit hoverCoordinates(static_cast<int>(hoveredTilePosition.x()),
                                  static_cast<int>(hoveredTilePosition.y()));
        }
    }
}


void MapWidget::mousePressEvent(QMouseEvent * event) {
    if (event->button() == Qt::LeftButton) {
        leftMouseButtonDown = true;
        applyCurrentSelectedTile();
        event->accept();
    }
    else {
        QWidget::mousePressEvent(event);
    }
}


void MapWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftMouseButtonDown = false;
        event->accept();
    }
    else {
        QWidget::mouseReleaseEvent(event);
    }
}


void MapWidget::paintEvent(QPaintEvent * event) {

    auto start = std::chrono::system_clock::now();

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }

    for (auto layer : collectVisibleLayers()) {
        layer->draw(painter, getTileSize());
    }
    
    drawHoveredTile(painter);

    auto end = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    averagePaintDuration << milliseconds;
}


void MapWidget::setAxisVisible(bool visible) {
    if (isAxisVisible() != visible) {
        axisVisible = visible;
        update();
    }
}


void MapWidget::setGridVisible(bool visible) {
    if (isGridVisible() != visible) {
        gridVisible = visible;
        update();
    }
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
    
    connect(map.data(), &Nameable::nameChanged, this, &MapWidget::mapNameChanged);
   
    mapSizeChanged();
    auto coordinateSystem = map->getCoordinateSystem();
    auto backgroundLayer = map->getLayers().getBackgroundLayer();
    
    connect(coordinateSystem.data(), &CoordinateSystem::sizeChanged, this, &MapWidget::mapSizeChanged);
    connect(coordinateSystem.data(), &CoordinateSystem::marginChanged, this, &MapWidget::mapSizeChanged);
}


void MapWidget::setTileSize(int tileSize) {
    
    if (tileSize == getTileSize()) {
        return;
    }
    
    if (tileSize < 0) {
        throw std::runtime_error{"Tile size of map is negative."};
    }
    
    this->tileSize = tileSize;
    mapSizeChanged();
    update();
}


std::tuple<QPointF, bool> MapWidget::widgetToMapCoordinates(float x, float y) const {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to render.");
    }
    
    auto coordinateSystem = map->getCoordinateSystem();
    auto rect = coordinateSystem->getInnerRect(getTileSize());
    
    auto mapX = (x - rect.x()) / static_cast<float >(getTileSize());
    auto mapY = (y - rect.y()) / static_cast<float >(getTileSize());
    
    auto size = coordinateSystem->getSize();
    auto inside = (mapX >= 0) && (mapX < size.width()) && (mapY >= 0) && (mapY < size.height());
    
    return {QPointF{mapX, mapY}, inside};
}

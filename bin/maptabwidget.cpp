/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QPixmapCache>
#include <QScrollArea>

#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

#include "maptabwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


MapTabWidget::MapTabWidget(QWidget * parent) : QTabWidget{parent} {
    connect(this, &QTabWidget::currentChanged, this, &MapTabWidget::currentChanged);
    connect(this, &QTabWidget::tabCloseRequested, this, &MapTabWidget::mapCloseRequested);
}


void MapTabWidget::closeCurrentMap() {
    removeTab(currentIndex());
}


void MapTabWidget::currentChanged(int index) {
    
    auto session = Session::getCurrentSession();
    if (index == -1) {
        session->selectMap(QString::null);
        return;
    }
    
    auto mapScrollArea = dynamic_cast<MapScrollArea *>(widget(index));
    if (!mapScrollArea) {
        return;
    }

    auto mapWidget = dynamic_cast<MapWidget *>(mapScrollArea->widget());
    if (!mapWidget) {
        return;
    }
    
    session->selectMap(mapWidget->getMapName());
}


void MapTabWidget::mapCloseRequested(int index) {
    if (index != -1) {
        removeTab(index);
    }
}


void MapTabWidget::mapNameChanged(QString oldName, QString newName) {
    
    auto iter = mapScrollAreas.find(oldName);
    if (iter == mapScrollAreas.end()) {
        return;
    }
    
    mapScrollAreas[newName] = (*iter).second;
    mapScrollAreas.erase(iter);
    auto tabIndex = indexOf((*iter).second);
    if (tabIndex == -1) {
        return;
    }
    setTabText(tabIndex, newName);
}


void MapTabWidget::redrawCurrentMap() {
    auto widget = currentWidget();
    if (widget == nullptr) {
        return;
    }
    widget->repaint();
}


void MapTabWidget::removeAllMaps() {
    
    for (auto & pair : mapScrollAreas) {
        int tabIndex = indexOf(pair.second);
        if (tabIndex != -1) {
            removeTab(tabIndex);
        }
    }
    
    mapScrollAreas.clear();
}


void MapTabWidget::removeMap(QString mapName) {

    auto pair = mapScrollAreas.find(mapName);
    if (pair != mapScrollAreas.end()) {
        
        int tabIndex = indexOf((*pair).second);
        mapScrollAreas.erase(pair);
        if (tabIndex != -1) {
            removeTab(tabIndex);
        }
    }
}


void MapTabWidget::selectMap(QString mapName) {

    if (mapName.isEmpty()) {
        return;
    }

    static QPixmap pixmap;
    if (pixmap.isNull()) {
        QPixmapCache::find("map", &pixmap);
    }

    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error{"Invalid map to select in tab."};
    }
    connect(map.data(), &Nameable::nameChanged, this, &MapTabWidget::mapNameChanged);
    
    auto iter = mapScrollAreas.find(mapName);
    if (iter == mapScrollAreas.end()) {

        auto mapWidget = new MapWidget{this};
        mapWidget->setMap(mapName);
        
        connect(mapWidget, &MapWidget::hoverCoordinates, this, &MapTabWidget::hoverCoordinates);
        connect(mapWidget, &MapWidget::rotateTileLeft, this, &MapTabWidget::rotateTileLeft);
        connect(mapWidget, &MapWidget::rotateTileRight, this, &MapTabWidget::rotateTileRight);

        auto mapScrollArea = new MapScrollArea{this, mapWidget};
        connect(mapScrollArea, &MapScrollArea::decreaseZoom, this, &MapTabWidget::decreaseZoom);
        connect(mapScrollArea, &MapScrollArea::increaseZoom, this, &MapTabWidget::increaseZoom);
        
        mapScrollAreas.emplace(mapName, mapScrollArea);
        addTab(mapScrollArea, pixmap, map->getName());
        setCurrentWidget(mapScrollArea);
    }
    else {

        if (indexOf((*iter).second) == -1) {
            addTab((*iter).second, pixmap, map->getName());
        }
        setCurrentWidget((*iter).second);
    }
}

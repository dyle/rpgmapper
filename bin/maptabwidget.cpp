/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QPixmapCache>
#include <QScrollArea>

#include "maptabwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


MapTabWidget::MapTabWidget(QWidget * parent) : QTabWidget{parent} {
    connect(this, &QTabWidget::tabCloseRequested, this, &MapTabWidget::mapCloseRequested);
}


void MapTabWidget::closeCurrentMap() {
    removeTab(currentIndex());
}


void MapTabWidget::connectSelectionSignals() {
    if (selection == nullptr) {
        return;
    }
    connect(selection->getAtlas().data(), &Atlas::mapRemoved, this, &MapTabWidget::mapRemoved);
    connect(selection.data(), &Selection::mapSelected, this, &MapTabWidget::mapSelected);
}


void MapTabWidget::mapRemoved(QString const &mapName) {

    auto iter = mapScrollAreas.find(mapName);
    if (iter != mapScrollAreas.end()) {
        int nTabIndex = indexOf((*iter).second);
        mapScrollAreas.erase(iter);
        if (nTabIndex != -1) {
            removeTab(nTabIndex);
        }
    }
}


void MapTabWidget::mapCloseRequested(int nIndex) {
    if (nIndex != -1) {
        removeTab(nIndex);
    }
}


void MapTabWidget::mapSelected(QString const & mapName) {

    static QPixmap pixmap;
    if (pixmap.isNull()) {
        QPixmapCache::find("map", &pixmap);
    }

    auto map = selection->getAtlas()->findMap(mapName);
    auto iter = mapScrollAreas.find(mapName);
    if (iter == mapScrollAreas.end()) {

        auto mapWidget = new MapWidget{this};
        mapWidget->setMap(map);
        connect(mapWidget, &MapWidget::hoverCoordinates, this, &MapTabWidget::hoverCoordinates);

        auto mapView = new MapScrollArea{this, mapWidget};
        mapScrollAreas.emplace(mapName, mapView);
        addTab(mapView, pixmap, map->getName());

        setCurrentWidget(mapView);
    }
    else {

        if (indexOf((*iter).second) == -1) {
            addTab((*iter).second, pixmap, map->getName());
        }
        setCurrentWidget((*iter).second);
    }
}


void MapTabWidget::setSelection(rpgmapper::model::SelectionPointer & selection) {
    this->selection = selection;
    connectSelectionSignals();
}

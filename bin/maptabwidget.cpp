/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QPixmapCache>
#include <QScrollArea>

#include "maptabwidget.hpp"

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

using namespace rpgmapper::model;
using namespace rpgmapper::view;


MapTabWidget::MapTabWidget(QWidget * parent) : QTabWidget{parent} {
    connect(this, &QTabWidget::tabCloseRequested, this, &MapTabWidget::mapCloseRequested);
}


void MapTabWidget::changedMapName(UNUSED QString regionName, QString nameBefore, QString nameAfter) {

    auto iter = mapScrollAreas.find(nameBefore);
    if (iter == mapScrollAreas.end()) {
        return;
    }

    mapScrollAreas[nameAfter] = (*iter).second;
    mapScrollAreas.erase(iter);
    auto tabIndex = indexOf((*iter).second);
    if (tabIndex == -1) {
        return;
    }
    setTabText(tabIndex, nameAfter);
}


void MapTabWidget::closeCurrentMap() {
    removeTab(currentIndex());
}


void MapTabWidget::connectSelectionSignals() {
    if (selection == nullptr) {
        return;
    }
    connect(selection->getAtlas().data(), &Atlas::mapNameChanged, this, &MapTabWidget::changedMapName);
    connect(selection->getAtlas().data(), &Atlas::mapRemoved, this, &MapTabWidget::removedMap);
    connect(selection.data(), &Selection::mapSelected, this, &MapTabWidget::selectedMap);
}


void MapTabWidget::mapCloseRequested(int nIndex) {
    if (nIndex != -1) {
        removeTab(nIndex);
    }
}


void MapTabWidget::redrawCurrentMap() {
    auto widget = currentWidget();
    if (widget == nullptr) {
        return;
    }
    widget->repaint();
}


void MapTabWidget::removedAllMaps() {
    for (auto & pair : mapScrollAreas) {
        int tabIndex = indexOf(pair.second);
        if (tabIndex != -1) {
            removeTab(tabIndex);
        }
    }
    mapScrollAreas.clear();
}


void MapTabWidget::removedMap(UNUSED QString regionName, QString mapName) {

    auto pair = mapScrollAreas.find(mapName);
    if (pair != mapScrollAreas.end()) {
        int tabIndex = indexOf((*pair).second);
        mapScrollAreas.erase(pair);
        if (tabIndex != -1) {
            removeTab(tabIndex);
        }
    }
}


void MapTabWidget::selectedMap(QString mapName) {

    if (mapName.isEmpty()) {
        return;
    }

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

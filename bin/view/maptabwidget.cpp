/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

#include <cassert>
#include <QPixmapCache>
#include <QScrollArea>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>
#include "mapscrollarea.hpp"
#include "maptabwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace view {


/**
 * Internal data of a MapTabWidget.
 */
class MapTabWidget::MapTabWidget_data {

public:

    MapTabWidget_data() = default;

    std::map<mapid_t, MapScrollArea *> m_cMapViews;     /**< all current map views */
};


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent     parent widget
 */
MapTabWidget::MapTabWidget(QWidget * cParent) : QTabWidget{cParent} {

    d = std::make_shared<MapTabWidget::MapTabWidget_data>();

    connect(this, &QTabWidget::tabCloseRequested, this, &MapTabWidget::mapCloseRequested);
    connect(Controller::instance().atlas().data(), &Atlas::deletedMap, this, &MapTabWidget::deletedMap);
    connect(Controller::instance().atlas().data(), &Atlas::selectedMap, this, &MapTabWidget::selectMap);
}


/**
 * Closes the current map.
 */
void MapTabWidget::closeCurrentMap() {
    removeTab(currentIndex());
}


/**
 * A map has been deleted.
 *
 * @param   nMapId      id of the map deleted
 */
void MapTabWidget::deletedMap(rpgmapper::model::mapid_t nMapId) {

    auto iter = d->m_cMapViews.find(nMapId);
    if (iter != d->m_cMapViews.end()) {

        int nTabIndex = indexOf((*iter).second);
        d->m_cMapViews.erase(iter);
        if (nTabIndex != -1) {
            removeTab(nTabIndex);
        }
    }
}


/**
 * The map widget close button has been clicked by the user.
 *
 * @param   nIndex          index of tab
 */
void MapTabWidget::mapCloseRequested(int nIndex) {
    if (nIndex != -1) {
        removeTab(nIndex);
    }
}


/**
 * Select a map.
 *
 * @param   nMapId      ID of the map
 */
void MapTabWidget::selectMap(mapid_t nMapId) {

    if (nMapId < 0) {
        return;
    }

    static QPixmap cPixmap;
    if (cPixmap.isNull()) {
        QPixmapCache::find("map", &cPixmap);
    }

    auto cMap = Controller::instance().atlas()->mapById(nMapId);
    auto iter = d->m_cMapViews.find(nMapId);
    if (iter == d->m_cMapViews.end()) {

        auto cMapWidget = new MapWidget{this, cMap};
        connect(cMapWidget, &MapWidget::hoverCoordinates, this, &MapTabWidget::hoverCoordinates);

        auto cMapView = new MapScrollArea{this, cMapWidget};
        d->m_cMapViews.emplace(nMapId, cMapView);
        addTab(cMapView, cPixmap, cMap->name());

        setCurrentWidget(cMapView);
    }
    else {

        if (indexOf((*iter).second) == -1) {
            addTab((*iter).second, cPixmap, cMap->name());
        }
        setCurrentWidget((*iter).second);
    }
}

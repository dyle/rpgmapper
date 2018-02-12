/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// defs

#define STANDARD_TILE_SIZE      48


// ------------------------------------------------------------
// incs

#include <iostream>

#include <QMouseEvent>
#include <QPainter>

// rpgmapper
#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/map.hpp>
#include "mapwidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace view {


/**
 * Internal data of a MapView.
 */
class MapWidget::MapView_data {

public:

    MapView_data() = default;

    MapPointer m_cMap;                  /**< Map to be viewed. */
};


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent     parent widget
 * @param   cMap        the map to be drawn
 */
MapWidget::MapWidget(QWidget * cParent, MapPointer & cMap) : QWidget{cParent} {

    d = std::make_shared<MapWidget::MapView_data>();
    d->m_cMap = cMap;

    setMouseTracking(true);

    connect(d->m_cMap.data(), &Map::changedSize, this, &MapWidget::changedMap);

    changedMap();
}


/**
 * The map has changed.
 */
void MapWidget::changedMap() {

    QSize cSize{d->m_cMap->size().width() + 2, d->m_cMap->size().height() + 2};
    cSize *= STANDARD_TILE_SIZE;
    resize(cSize);
}


/**
 * The mouse has been moved over the widget.
 *
 * @param   cEvent      mouse move event
 */
void MapWidget::mouseMoveEvent(QMouseEvent * cEvent) {

    QWidget::mouseMoveEvent(cEvent);
    int x = cEvent->pos().x() / STANDARD_TILE_SIZE - 1;
    int y = cEvent->pos().y() / STANDARD_TILE_SIZE - 1;
    emit hoverCoordinates(x, y);
}


/**
 * Draw the map.
 *
 * @param   cEvent      paint event
 */
void MapWidget::paintEvent(QPaintEvent * cEvent) {

    QWidget::paintEvent(cEvent);

    QPainter cPainter(this);
    cPainter.setRenderHint(QPainter::Antialiasing);
    cPainter.setTransform(QTransform::fromTranslate(STANDARD_TILE_SIZE, STANDARD_TILE_SIZE));
    cPainter.setViewTransformEnabled(true);

    for (auto const & cPair : d->m_cMap->layers()) {
        cPair.second->draw(cPainter, STANDARD_TILE_SIZE);
    }
}

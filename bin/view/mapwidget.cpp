/*
 * mapview.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// ------------------------------------------------------------
// defs

#define MINIMUM_ZOOM            0.25
#define MAXIMUM_ZOOM            8.0
#define STANDARD_TILE_SIZE      64


// ------------------------------------------------------------
// incs

#include <iostream>

#include <QPainter>

// rpgmapper
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
    float m_nScaleFactor = 1.0;         /**< Current scale factor value. */
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

    connect(d->m_cMap.data(), &Map::changedSize, this, &MapWidget::changedMap);

    changedMap();
}


/**
 * The map has changed.
 */
void MapWidget::changedMap() {
    resize(d->m_cMap->size() * STANDARD_TILE_SIZE * scaleFactor());
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

    // TODO: setWindow to make logical to world coordinates
    // TODO: add space for map text

    cPainter.fillRect(rect(), QColor{0, 0, 96, 255});
}


/**
 * Get the current scale factor value.
 *
 * @return  the current scale factor value
 */
float MapWidget::scaleFactor() const {
    return d->m_nScaleFactor;
}


/**
 * Set the current scale factor value.
 *
 * @param   nScaleFactor       the new scale factor value
 */
void MapWidget::scaleFactor(float nScaleFactor) {

    if (d->m_nScaleFactor == nScaleFactor) {
        return;
    }
    if ((nScaleFactor < MINIMUM_ZOOM) || (nScaleFactor > MAXIMUM_ZOOM)) {
        return;
    }

    d->m_nScaleFactor = nScaleFactor;
}

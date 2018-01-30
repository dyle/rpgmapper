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

#define STANDARD_TILE_SIZE      48


// ------------------------------------------------------------
// incs

#include <QPainter>

// rpgmapper
#include <rpgmapper/layer.hpp>
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

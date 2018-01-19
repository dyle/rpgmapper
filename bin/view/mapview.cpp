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
// incs

#include <iostream>

// rpgmapper
#include <rpgmapper/common_macros.h>
#include <rpgmapper/map.hpp>
#include "mapview.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace view {


/**
 * Internal data of a MapView.
 */
class MapView::MapView_data {

public:

    MapView_data() = default;

    MapPointer m_cMap;                  /**< map to be viewed */
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
MapView::MapView(QWidget * cParent, MapPointer & cMap) : QWidget{cParent} {
    d = std::make_shared<MapView::MapView_data>();
    d->m_cMap = cMap;
}


/**
 * Draw the map.
 *
 * @param   cEvent      paint event
 */
void MapView::paintEvent(UNUSED QPaintEvent * cEvent) {

    std::cout << "MapView::paintEvent() - 1: this=" << this << std::endl;
    std::cout << "MapView::paintEvent() - 2: d->m_cMap.name()=" << d->m_cMap->name().toStdString() << std::endl;

}


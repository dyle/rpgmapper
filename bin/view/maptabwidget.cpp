/*
 * maptabwidget.cpp
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

#include <cassert>
#include <QPixmapCache>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>
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

    std::map<mapid_t, QWidget *> m_cMapViews;       /**< all current map views */
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
}


/**
 * Select a map.
 *
 * @param   nMapId      ID of the map
 */
void MapTabWidget::selectMap(mapid_t nMapId) {

    auto iter = d->m_cMapViews.find(nMapId);
    if (iter == d->m_cMapViews.end()) {

        auto cMap = Controller::instance().atlas()->maps()[nMapId];
        assert(cMap.data());

        auto cMapView = new QWidget{this};
        d->m_cMapViews.emplace(nMapId, cMapView);

        QPixmap cPixmap;
        QPixmapCache::find("map", &cPixmap);
        addTab(cMapView, cPixmap, cMap->name());
    }
    else {
        setCurrentWidget((*iter).second);
    }
}

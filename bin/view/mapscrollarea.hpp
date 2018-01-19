/*
 * mapscrollarea.hpp
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


#ifndef VIEW_MAPSCROLLAREA_HPP
#define VIEW_MAPSCROLLAREA_HPP


// ------------------------------------------------------------
// incs

#include <QScrollArea>

// rpgmapper
#include "mapwidget.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace view {


/**
 * A MapScrollArea can show a scrollable map widget
 */
class MapScrollArea : public QScrollArea {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent         parent widget
     * @param   cMapWidget      the map widget enclosed
     */
    explicit MapScrollArea(QWidget * cParent, MapWidget * cMapWidget);


    /**
     * Return the internal MapWidget
     *
     * @return  the pointer to the internal map widget
     */
    MapWidget * mapWidget() { return dynamic_cast<MapWidget *>(widget()); }

};

}
}


#endif

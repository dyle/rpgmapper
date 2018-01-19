/*
 * mapview.hpp
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


#ifndef VIEW_MAPVIEW_HPP
#define VIEW_MAPVIEW_HPP


// ------------------------------------------------------------
// incs

#include <memory>
#include <QWidget>

// rpgmapper
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace view {


/**
 * A MapView is the widget which draws a map.
 */
class MapView : public QWidget {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent     parent widget
     * @param   cMap        the map to be drawn
     */
    explicit MapView(QWidget * cParent, rpgmapper::model::MapPointer & cMap);


protected:


    /**
     * Draw the map.
     *
     * @param   cEvent      paint event
     */
    void paintEvent(QPaintEvent * cEvent) override;


    class MapView_data;                              /**< Internal data type. */
    std::shared_ptr<MapView::MapView_data> d;        /**< Internal data instance. */
};

}
}


#endif

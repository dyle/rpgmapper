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


#ifndef VIEW_MAPWIDGET_HPP
#define VIEW_MAPWIDGET_HPP


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
 * A MapWidget is the widget which draws a map.
 */
class MapWidget : public QWidget {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent     parent widget
     * @param   cMap        the map to be drawn
     */
    explicit MapWidget(QWidget * cParent, rpgmapper::model::MapPointer & cMap);


    /**
     * Get the current scale factor value.
     *
     * @return  the current scale factor value
     */
    float scaleFactor() const;


    /**
     * Set the current scale factor value.
     *
     * @param   nScaleFactor       the new scale factor value
     */
    void scaleFactor(float nScaleFactor);


public slots:


    /**
     * The map has changed.
     */
    void changedMap();


protected:


    /**
     * Draw the map.
     *
     * @param   cEvent      paint event
     */
    void paintEvent(QPaintEvent * cEvent) override;


    class MapView_data;                              /**< Internal data type. */
    std::shared_ptr<MapWidget::MapView_data> d;        /**< Internal data instance. */
};

}
}


#endif

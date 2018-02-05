/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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


public slots:


    /**
     * The map has changed.
     */
    void changedMap();


signals:


    /**
     * The mouse of the user hovers some map coordinates.
     *
     * @param   x       X map coordinate (with origin top/left)
     * @param   y       Y map coordinate (with origin top/left)
     */
    void hoverCoordinates(int x, int y);


protected:


    /**
     * The mouse has been moved over the widget.
     *
     * @param   cEvent      mouse move event
     */
    void mouseMoveEvent(QMouseEvent * cEvent) override;


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

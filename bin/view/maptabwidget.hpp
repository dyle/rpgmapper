/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_MAPTABWIDGET_HPP
#define VIEW_MAPTABWIDGET_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QTabWidget>

// rpgmapper
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace view {


/**
 * A QTreeWidget which displays the Atlas structure.
 */
class MapTabWidget : public QTabWidget {


Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent     parent widget
     */
    explicit MapTabWidget(QWidget * cParent = nullptr);


public slots:


    /**
     * Closes the current map.
     */
    void closeCurrentMap();


    /**
     * A map has been deleted.
     *
     * @param   nMapId      id of the map deleted
     */
    void deletedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * Select a map.
     *
     * @param   nMapId      ID of the map
     */
    void selectMap(rpgmapper::model::mapid_t nMapId);


private slots:


    /**
     * The map widget close button has been clicked by the user.
     *
     * @param   nIndex          index of tab
     */
    void mapCloseRequested(int nIndex);


signals:


    /**
     * The mouse of the user hovers some current map coordinates.
     *
     * @param   x       X map coordinate (with origin top/left)
     * @param   y       Y map coordinate (with origin top/left)
     */
    void hoverCoordinates(int x, int y);


private:


    class MapTabWidget_data;                               /**< Internal data type. */
    std::shared_ptr<MapTabWidget::MapTabWidget_data> d;    /**< Internal data instance. */

};


}
}


#endif

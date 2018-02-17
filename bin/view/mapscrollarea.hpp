/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_MAPSCROLLAREA_HPP
#define VIEW_MAPSCROLLAREA_HPP


// ------------------------------------------------------------
// incs

#include <QScrollArea>

// rpgmapper
#include "../mapwidget.hpp"


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

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAPSCROLLAREA_HPP
#define RPGMAPPER_VIEW_MAPSCROLLAREA_HPP


#include <QScrollArea>

#include "mapwidget.hpp"


namespace rpgmapper {
namespace view {

class MapScrollArea : public QScrollArea {

    Q_OBJECT

public:

    explicit MapScrollArea(QWidget * parent, MapWidget * mapWidget);

    MapWidget * mapWidget() {
        return dynamic_cast<MapWidget *>(widget());
    }
};

}
}


#endif

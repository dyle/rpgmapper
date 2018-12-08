/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QMouseEvent>
#include <QScrollBar>

#include "mapscrollarea.hpp"

using namespace rpgmapper::view;


MapScrollArea::MapScrollArea(QWidget * parent, MapWidget * mapWidget) : QScrollArea{parent} {

    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setBackgroundRole(QPalette::Dark);

    mapWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setWidget(mapWidget);
}


void MapScrollArea::mouseMoveEvent(QMouseEvent * event) {
    
    if (mouseButtonDown) {
        
        auto move = event->pos() - mousePosition;
        mousePosition = event->pos();
        
        int x = horizontalScrollBar()->value();
        horizontalScrollBar()->setValue(x - move.x());
        int y = verticalScrollBar()->value();
        verticalScrollBar()->setValue(y - move.y());
        
        event->accept();
    }
}


void MapScrollArea::mousePressEvent(QMouseEvent * event) {
    
    if (event->button() == Qt::RightButton) {
        mouseButtonDown = true;
        mousePosition = event->pos();
        event->accept();
    }
}

void MapScrollArea::mouseReleaseEvent(QMouseEvent * event) {
    
    if (event->button() == Qt::RightButton) {
        mouseButtonDown = false;
        event->accept();
    }
}

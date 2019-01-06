/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <QApplication>
#include <QCursor>
#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>

#include "mapscrollarea.hpp"

using namespace rpgmapper::view;


MapScrollArea::MapScrollArea(QWidget * parent, MapWidget * mapWidget) : QScrollArea{parent} {

    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setBackgroundRole(QPalette::Dark);
    
    connect(horizontalScrollBar(), &QAbstractSlider::valueChanged, this, &MapScrollArea::adjustHorizontalFactor);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged, this, &MapScrollArea::adjustVerticalFactor);

    mapWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setWidget(mapWidget);
}


void MapScrollArea::adjustHorizontalFactor() {
    
    auto max = horizontalScrollBar()->maximum();
    if (max) {
        horizontalPositionFactor = static_cast<float>(horizontalScrollBar()->value()) / max;
    }
    else {
        horizontalPositionFactor = 0.5;
    }
}


void MapScrollArea::adjustVerticalFactor() {
    
    auto max = verticalScrollBar()->maximum();
    if (max) {
        verticalPositionFactor = static_cast<float>(verticalScrollBar()->value()) / max;
    }
    else {
        verticalPositionFactor = 0.5;
    }
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
        QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
        mouseButtonDown = true;
        mousePosition = event->pos();
        event->accept();
    }
}

void MapScrollArea::mouseReleaseEvent(QMouseEvent * event) {
    
    if (event->button() == Qt::RightButton) {
        QApplication::restoreOverrideCursor();
        mouseButtonDown = false;
        event->accept();
    }
}


void MapScrollArea::mapResized() {
    auto horizontalValue = static_cast<int>(horizontalPositionFactor * horizontalScrollBar()->maximum());
    auto verticalValue = static_cast<int>(verticalPositionFactor * verticalScrollBar()->maximum());
    horizontalScrollBar()->setValue(horizontalValue);
    verticalScrollBar()->setValue(verticalValue);
}


void MapScrollArea::wheelEvent(QWheelEvent * event) {
    
    if (event->angleDelta().y() > 0) {
        emit increaseZoom();
    }
    if (event->angleDelta().y() < 0) {
        emit decreaseZoom();
    }
    event->accept();
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QPainter>
#include <QPalette>

#include "colorwidget.hpp"

using namespace rpgmapper::view;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


ColorWidget::ColorWidget(QColor color, QWidget * parent) : QWidget{parent} , color{color} {
    setMinimumSize(8, 8);
}


void ColorWidget::enterEvent(UNUSED QEvent * event) {
    update();
}


void ColorWidget::leaveEvent(UNUSED QEvent * event) {
    update();
}


void ColorWidget::paintEvent(UNUSED QPaintEvent * event) {
    
    QPainter painter(this);
    
    QPalette systemPalette;
    QRect rect{{0, 0}, size()};
    rect.adjust(0, 0, -1, -1);
    painter.fillRect(rect, systemPalette.color(QPalette::Window));
    
    if (underMouse()) {
        QColor highlghted = Qt::red;
        painter.setPen(highlghted);
        painter.drawRect(rect);
    }
    
    if (isSelected()) {
        painter.setPen(systemPalette.color(QPalette::Highlight));
        painter.drawRect(rect);
    }
    
    rect.adjust(1, 1, 0, 0);
    painter.fillRect(rect, color);
}


void ColorWidget::setColor(QColor color) {
    if (this->color != color) {
        this->color = color;
        update();
    }
}


void ColorWidget::setSelected(bool selected) {
    if (this->selected != selected) {
        this->selected = selected;
        emit selectedChanged();
    }
}

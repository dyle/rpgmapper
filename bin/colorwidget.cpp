/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>

#include "colorwidget.hpp"

using namespace rpgmapper::view;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


ColorWidget::ColorWidget(QColor color, int id, QWidget * parent) : QWidget{parent}, color{color}, id{id} {
    setMinimumSize(8, 8);
}


void ColorWidget::enterEvent(UNUSED QEvent * event) {
    update();
}


void ColorWidget::leaveEvent(UNUSED QEvent * event) {
    update();
}


void ColorWidget::mouseDoubleClickEvent(UNUSED QMouseEvent * event) {
    
    auto color = QColorDialog::getColor(getColor(), this);
    if (!color.isValid()) {
        return;
    }
    setColor(color);
    emit colorChanged(id);
}


void ColorWidget::mouseReleaseEvent(QMouseEvent * event) {
    if ((event->button() == Qt::LeftButton) && !isSelected()) {
        setSelected(true);
    }
}

void ColorWidget::paintEvent(UNUSED QPaintEvent * event) {
    
    QPainter painter(this);
    
    QPalette systemPalette;
    QRect rect{{0, 0}, size()};
    rect.adjust(0, 0, -1, -1);
    painter.fillRect(rect, systemPalette.color(QPalette::Window));
    
    if (underMouse()) {
        painter.setPen(hoverColor);
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


void ColorWidget::setHoveringColor(QColor color) {
    if (hoverColor != color) {
        hoverColor = color;
        update();
    }
}


void ColorWidget::setSelected(bool selected) {
    
    if (this->selected != selected) {
        this->selected = selected;
        emit selectedChanged(id, selected);
        update();
    }
}

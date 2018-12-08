/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QGridLayout>

#include "recentcolorswidget.hpp"

using namespace rpgmapper::view;


RecentColorsWidget::RecentColorsWidget(QWidget * parent) : QWidget{parent} {
    
    auto layout = new QGridLayout{this};
    layout->setMargin(0);
    layout->setSpacing(0);
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            colorWidgets[i][j] = new ColorWidget{Qt::white, i * 8 + j, this};
            connect(colorWidgets[i][j], &ColorWidget::selectedChanged, this, &RecentColorsWidget::colorSelectedChange);
            layout->addWidget(colorWidgets[i][j], i, j);
        }
    }
}


void RecentColorsWidget::colorSelectedChange(int id, bool selected) {
    
    if ((id < 0) || (id >= 2 * 8)) {
        return;
    }
    
    if ((selectedIndex != id) && selected && (selectedIndex != -1)) {
        colorWidgets[selectedIndex / 8][selectedIndex % 8]->setSelected(false);
    }
    
    if (selected) {
        selectedIndex = id;
    }
}



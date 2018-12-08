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
            colorWidgets[i][j] = new ColorWidget{Qt::white, this};
            layout->addWidget(colorWidgets[i][j], i, j);
        }
    }
}

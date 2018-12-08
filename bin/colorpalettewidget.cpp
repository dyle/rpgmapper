/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QGridLayout>

#include "colorpalettewidget.hpp"

using namespace rpgmapper::view;


ColorPaletteWidget::ColorPaletteWidget(QWidget * parent) : QWidget{parent} {

    auto layout = new QGridLayout{this};
    layout->setMargin(0);
    layout->setSpacing(0);
    
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            colorWidgets[i][j] = new ColorWidget{Qt::white, this};
            layout->addWidget(colorWidgets[i][j], i, j);
        }
    }
}


void ColorPaletteWidget::setPalette(rpgmapper::model::ColorPalette const & palette) {
    
    this->palette = palette;
    
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            colorWidgets[i][j]->setColor(palette.getPalette()[i][j]);
        }
    }
}

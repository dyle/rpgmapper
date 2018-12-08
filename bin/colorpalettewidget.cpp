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
            colorWidgets[i][j] = new ColorWidget{Qt::white, i * 16 + j, this};
            connect(colorWidgets[i][j], &ColorWidget::selectedChanged, this, &ColorPaletteWidget::colorSelectedChange);
            layout->addWidget(colorWidgets[i][j], i, j);
        }
    }
}


void ColorPaletteWidget::colorSelectedChange(int id, bool selected) {
    
    if ((id < 0) || (id >= 16 * 16)) {
        return;
    }
    
    if ((selectedIndex != id) && selected && (selectedIndex != -1)) {
        colorWidgets[selectedIndex / 16][selectedIndex % 16]->setSelected(false);
    }
    
    if (selected) {
        selectedIndex = id;
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

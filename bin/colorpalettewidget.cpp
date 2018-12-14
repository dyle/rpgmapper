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
            int index = i * 16 + j;
            colorWidgets[index] = new ColorWidget{Qt::white, index, this};
            connect(colorWidgets[index], &ColorWidget::selectedChanged, this, &ColorPaletteWidget::colorSelectedChange);
            layout->addWidget(colorWidgets[index], i, j);
        }
    }
}


void ColorPaletteWidget::colorSelectedChange(int id, bool selected) {
    
    if ((id < 0) || (id >= 16 * 16)) {
        return;
    }
    
    if (!selected) {
        
        colorWidgets[id]->setSelected(false);
        if (selectedIndex == id) {
            selectedIndex = -1;
        }
    }
    else {
        
        colorWidgets[id]->setSelected(true);
        if (selectedIndex != id) {
            selectedIndex = id;
            emit colorSelected(colorWidgets[selectedIndex]->getColor());
        }
    }
}


void ColorPaletteWidget::setPalette(rpgmapper::model::ColorPalette const & palette) {
    
    this->palette = palette;
    for (int i = 0; i < 16 * 16; ++i) {
        colorWidgets[i]->setColor(palette.getPalette()[i]);
    }
}

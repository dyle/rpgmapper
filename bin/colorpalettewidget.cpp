/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QGridLayout>

#include <rpgmapper/colorpalette.hpp>

#include "colorpalettewidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


ColorPaletteWidget::ColorPaletteWidget(QWidget * parent) : QWidget{parent} {

    auto layout = new QGridLayout{this};
    layout->setMargin(0);
    layout->setSpacing(0);
    
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            
            int index = i * 16 + j;
            
            colorWidgets[index] = new ColorWidget{Qt::white, index, this};
            
            connect(colorWidgets[index],
                    &ColorWidget::colorChanged,
                    this,
                    &ColorPaletteWidget::colorChanged);
            
            connect(colorWidgets[index],
                    &ColorWidget::selectedChanged,
                    this,
                    &ColorPaletteWidget::selectedColorChange);
            
            layout->addWidget(colorWidgets[index], i, j);
        }
    }
}


void ColorPaletteWidget::colorChanged(int id) {
    
    if ((id < 0) || (id >= 16 * 16)) {
        return;
    }
    
    emit colorChangedInPalette(id, colorWidgets[id]->getColor());
    selectedColorChange(id, true);
}


void ColorPaletteWidget::selectedColorChange(int id, bool selected) {
    
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
        
        for (int i = 0; i < static_cast<int>(colorWidgets.size()); ++i) {
            if (i != id) {
                colorWidgets[i]->setSelected(false);
            }
        }
        
        colorWidgets[id]->setSelected(true);
        selectedIndex = id;
        emit colorSelected(colorWidgets[selectedIndex]->getColor());
    }
}


void ColorPaletteWidget::setPalette(rpgmapper::model::ColorPalettePointer palette) {
    for (int i = 0; i < 16 * 16; ++i) {
        colorWidgets[i]->setColor(palette->getPalette()[i]);
    }
}

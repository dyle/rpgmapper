/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource.hpp>
#include <rpgmapper/resource_db.hpp>

#include "colorchooserwidget.hpp"
#include "ui_colorchooserwidget.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


ColorChooserWidget::ColorChooserWidget(QWidget * parent) : QWidget{parent} {
    ui = std::make_shared<Ui_ColorChooserWidget>();
    ui->setupUi(this);
}


void ColorChooserWidget::loadPalettes() {
    
    palettes.clear();
    auto colorPalettesResourcePrefix = ResourceDB::getLocation(ResourceDB::Location::colorpalettes);
    for (auto const & resourceName : ResourceDB::getResources(colorPalettesResourcePrefix)) {
    
        auto res = ResourceDB::getResource(resourceName);
        if (res) {
        
            auto palette = ColorPalette::load(res->getData());
            if (palette.isValid()) {
                palettes.emplace(resourceName, palette);
            }
        }
    }
}


/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QJsonArray>
#include <QJsonDocument>

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
        
        Palette palette;
        if (loadPalette(palette, resourceName)) {
            palettes.emplace(resourceName, palette);
        }
    }
}


bool ColorChooserWidget::loadPalette(ColorChooserWidget::Palette & palette, QString const & resourceName) const {
    
    auto res = ResourceDB::getResource(resourceName);
    if (!res) {
        return false;
    }
    
    auto json = QJsonDocument::fromJson(res->getData());
    if (!json.isArray()) {
        return false;
    }
    
    auto jsonArray = json.array();
    for (int i = 0; i < std::min(jsonArray.size(), 16*16); ++i) {
        if (jsonArray.at(i).isString()) {
            auto colorString = jsonArray.at(i).toString();
            palette[i / 16][i % 16] = QColor{colorString};
        }
    }
    
    return true;
}

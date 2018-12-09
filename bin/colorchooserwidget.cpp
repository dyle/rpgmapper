/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QComboBox>

#include <rpgmapper/resource.hpp>
#include <rpgmapper/resource_db.hpp>

#include "colorchooserwidget.hpp"
#include "ui_colorchooserwidget.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


ColorChooserWidget::ColorChooserWidget(QWidget * parent) : QWidget{parent} {
    
    ui = std::make_shared<Ui_ColorChooserWidget>();
    ui->setupUi(this);
    
    connect(ui->paletteBox, SIGNAL(activated(int)), this, SLOT(selectedPaletteChanged()));
    connect(ui->scrollAreaWidgetContents, SIGNAL(colorSelected(QColor)), this, SIGNAL(colorSelected(QColor)));
}


void ColorChooserWidget::loadPalettes() {
    
    palettes.clear();
    ui->paletteBox->clear();
    
    auto colorPalettesResourcePrefix = ResourceDB::getLocation(ResourceDB::Location::colorpalettes);
    for (auto const & resourceName : ResourceDB::getResources(colorPalettesResourcePrefix)) {
    
        auto res = ResourceDB::getResource(resourceName);
        if (res) {
    
            auto paletteId = resourceName.right(resourceName.size() - colorPalettesResourcePrefix.size() - 1);
            auto palette = ColorPalette::load(res->getData());
            if (palette.isValid() && !paletteId.isEmpty()) {
                palettes.emplace(paletteId, palette);
                ui->paletteBox->addItem(paletteId);
            }
        }
    }
    
    selectedPaletteChanged();
}


void ColorChooserWidget::selectedPaletteChanged() {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    ui->scrollAreaWidgetContents->setPalette((*iter).second);
}

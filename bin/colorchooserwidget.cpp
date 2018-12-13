/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

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
    connect(ui->editButton, SIGNAL(clicked(bool)), this, SLOT(editPalette()));
    connect(ui->loadButton, SIGNAL(clicked(bool)), this, SLOT(loadPalette()));
    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(savePalette()));
    connect(ui->colorPipetteButton, SIGNAL(clicked(bool)), this, SLOT(pickColor()));
}


void ColorChooserWidget::editPalette() {

}


void ColorChooserWidget::loadPalette() {

}


void ColorChooserWidget::loadPalettes() {
    
    palettes.clear();
    ui->paletteBox->clear();
    
    auto colorPalettesResourcePrefix = ResourceDB::getLocation(ResourceDB::Location::colorpalettes);
    for (auto const & resourceName : ResourceDB::getResources(colorPalettesResourcePrefix)) {
    
        auto res = ResourceDB::getResource(resourceName);
        if (res) {
    
            auto palette = ColorPalette::load(res->getData());
            if (palette.isValid() && !palette.getName().isEmpty()) {
                palettes.emplace(palette.getName(), palette);
                ui->paletteBox->addItem(palette.getName());
            }
        }
    }
    
    selectedPaletteChanged();
}


void ColorChooserWidget::pickColor() {

}


void ColorChooserWidget::saveCurrentPaletteToFile(QString filename) {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    auto colorPalette = (*iter).second;
    auto json = colorPalette.toJSON();
    
    QFile file{filename};
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this,
                tr("Save color palette"),
                tr("Failed to open file to save color palette."),
                QMessageBox::Ok);
        return;
    }
    file.write(json.toJson(QJsonDocument::Indented));
    file.close();
}


void ColorChooserWidget::savePalette() {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    
    QFileDialog savePaletteDialog(this);
    savePaletteDialog.setFileMode(QFileDialog::AnyFile);
    savePaletteDialog.setAcceptMode(QFileDialog::AcceptSave);
    savePaletteDialog.setWindowTitle(tr("Save color palette"));
    
    auto answer = savePaletteDialog.exec();
    if ((answer == 0) || savePaletteDialog.selectedFiles().empty()) {
        return;
    }
    
    saveCurrentPaletteToFile(savePaletteDialog.selectedFiles().first());
}


void ColorChooserWidget::selectedPaletteChanged() {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    ui->scrollAreaWidgetContents->setPalette((*iter).second);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QColorDialog>
#include <QComboBox>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <QMessageBox>

#include <rpgmapper/resource/colorpalette.hpp>
#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/resource_type.hpp>

#include "colorchooserwidget.hpp"
#include "ui_colorchooserwidget.h"

using namespace rpgmapper::model::resource;
using namespace rpgmapper::view;


ColorChooserWidget::ColorChooserWidget(QWidget * parent) : QWidget{parent} {
    
    ui = std::make_shared<Ui_ColorChooserWidget>();
    ui->setupUi(this);
    
    loadPaletteDialog = new QFileDialog{this};
    loadPaletteDialog->setFileMode(QFileDialog::ExistingFile);
    loadPaletteDialog->setAcceptMode(QFileDialog::AcceptOpen);
    loadPaletteDialog->setWindowTitle(tr("Load color palette"));
    
    savePaletteDialog = new QFileDialog{this};
    savePaletteDialog->setFileMode(QFileDialog::AnyFile);
    savePaletteDialog->setAcceptMode(QFileDialog::AcceptSave);
    savePaletteDialog->setWindowTitle(tr("Save color palette"));
    
    connect(ui->paletteBox, SIGNAL(activated(int)), this, SLOT(selectedPaletteChanged()));
    
    connect(ui->scrollAreaWidgetContents,
            SIGNAL(colorChangedInPalette(int, QColor)),
            this,
            SLOT(colorChanged(int, QColor)));
    connect(ui->scrollAreaWidgetContents, SIGNAL(colorSelected(QColor)), this, SIGNAL(colorSelected(QColor)));
    connect(ui->scrollAreaWidgetContents,
            &ColorPaletteWidget::colorSelected,
            this,
            &ColorChooserWidget::colorSelectedInPalette);
    
    connect(ui->recentColorsWidget, SIGNAL(colorSelected(QColor)), this, SIGNAL(colorSelected(QColor)));
    connect(ui->recentColorsWidget,
            &RecentColorsWidget::colorSelected,
            this,
            &ColorChooserWidget::colorSelectedInRecentList);
    
    connect(ui->editButton, SIGNAL(clicked(bool)), this, SLOT(editPalette()));
    connect(ui->copyButton, SIGNAL(clicked(bool)), this, SLOT(copyPalette()));
    connect(ui->loadButton, SIGNAL(clicked(bool)), this, SLOT(loadPalette()));
    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(savePalette()));
    connect(ui->colorPipetteButton, SIGNAL(clicked(bool)), this, SLOT(pickColor()));
}


void ColorChooserWidget::appliedTile() {
    ui->recentColorsWidget->appliedTile();
}


void ColorChooserWidget::changeName(QString const & oldName, QString const & newName) {
    
    auto iter = palettes.find(oldName);
    if (iter == palettes.end()) {
        return;
    }
    
    auto palette = (*iter).second;
    palette->setName(newName);
    palettes.erase(iter);
    palettes.emplace(newName, palette);
    
    int index = ui->paletteBox->findText(oldName);
    if (index != -1) {
        ui->paletteBox->removeItem(index);
    }
    ui->paletteBox->addItem(newName);
    index = ui->paletteBox->findText(newName);
    ui->paletteBox->setCurrentIndex(index);
    selectedPaletteChanged();
}


void ColorChooserWidget::colorChanged(int id, QColor color) {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    
    auto palette = (*iter).second;
    auto colorPalette = dynamic_cast<ColorPalette *>(palette.data());
    if (!colorPalette) {
        throw std::runtime_error{"Not a color palette resource pointer present, when expected."};
    }
    if ((id < 0) || (id >= static_cast<int>(colorPalette->getPalette().size()))) {
        return;
    }
    
    colorPalette->getPalette()[id] = std::move(color);
    colorPalette->setData(colorPalette->toJSON().toJson());
}


void ColorChooserWidget::colorSelectedInPalette() {

    auto selectedIndexInRecentList = ui->recentColorsWidget->getSelectedIndex();
    if (selectedIndexInRecentList >= 0) {
        ui->recentColorsWidget->selectedColorChange(selectedIndexInRecentList, false);
    }
}


void ColorChooserWidget::colorSelectedInRecentList() {
    
    auto selectedIndexInRecentList = ui->scrollAreaWidgetContents->getSelectedIndex();
    if (selectedIndexInRecentList >= 0) {
        ui->scrollAreaWidgetContents->selectedColorChange(selectedIndexInRecentList, false);
    }
}


void ColorChooserWidget::copyPalette() {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    
    auto newName = suggestNewName(ui->paletteBox->currentText());
    auto resourceLocationName = getResourcePrefixForType(ResourceType::colorpalette) + "/" + newName + ".json";
    auto copy = ResourcePointer{new ColorPalette{resourceLocationName, (*iter).second->getData()}};
    copy->setName(newName);
    
    palettes.emplace(newName, copy);
    auto localResources = ResourceDB::getLocalResources();
    localResources->addResource(copy);
    
    ui->paletteBox->addItem(newName);
    int index = ui->paletteBox->findText(newName);
    ui->paletteBox->setCurrentIndex(index);
    selectedPaletteChanged();
}


void ColorChooserWidget::editPalette() {
    
    auto currentPaletteText = ui->paletteBox->currentText();
    auto iter = palettes.find(currentPaletteText);
    if (iter == palettes.end()) {
        return;
    }
    
    bool done = false;
    do {
        
        auto newPaletteName = QInputDialog::getText(this,
                                                    tr("New name for the color palette"),
                                                    tr("Please specify a new name for this color palette:"),
                                                    QLineEdit::Normal,
                                                    currentPaletteText,
                                                    &done);
        
        if (!done || (newPaletteName == currentPaletteText)) {
            newPaletteName = QString::null;
            done = true;
        }
        else
        if (isNameAssigned(newPaletteName)) {
            QMessageBox::information(this,
                                     tr("New name for the color palette"),
                                     tr("This name is already assigned to a color palette.\n" \
                                        "Please choose another one."));
            done = false;
        }
        else {
            changeName(currentPaletteText, newPaletteName);
        }
        
    } while (!done);
}


bool ColorChooserWidget::isNameAssigned(QString const & name) const {
    
    QStringList knownNames;
    for (int i = 0; i < ui->paletteBox->count(); ++i) {
        knownNames.append(ui->paletteBox->itemText(i));
    }
    
    return knownNames.contains(name);
}


void ColorChooserWidget::loadPalette() {
    
    auto answer = loadPaletteDialog->exec();
    if ((answer == 0) || loadPaletteDialog->selectedFiles().empty()) {
        return;
    }
    loadPaletteFromFile(loadPaletteDialog->selectedFiles().first());
}


void ColorChooserWidget::loadPaletteFromFile(QString filename) {
    
    QFile file{filename};
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Load color palette"),
                              tr("Failed to open file to load color palette."),
                              QMessageBox::Ok);
        return;
    }
    
    auto data = file.readAll();
    file.close();
    lastFolderUsed = QFileInfo{file}.dir().absolutePath();
    
    // TODO: get the right name
    ResourcePointer palette{new ColorPalette{QString::null, data}};
    if (!palette->isValid()) {
        QMessageBox::critical(this,
                              tr("Load color palette"),
                              tr("File seems not to contain a color palette. Unable to load."),
                              QMessageBox::Ok);
        return;
    }
    
    auto paletteName = palette->getName();
    auto iter = palettes.find(paletteName);
    if (iter != palettes.end()) {
        palettes.erase(iter);
    }
    palettes.emplace(paletteName, palette);
    
    auto localResources = ResourceDB::getLocalResources();
    localResources->addResource(palette);
    
    int index = ui->paletteBox->findText(paletteName);
    if (index != -1) {
        ui->paletteBox->removeItem(index);
    }
    ui->paletteBox->addItem(paletteName);
    index = ui->paletteBox->findText(paletteName);
    ui->paletteBox->setCurrentIndex(index);
    selectedPaletteChanged();
}


void ColorChooserWidget::loadPalettes() {
    
    palettes.clear();
    ui->paletteBox->clear();
    
    auto colorPalettesResourcePrefix = getResourcePrefixForType(ResourceType::colorpalette);
    auto colorPaletteResourceNames = ResourceDB::getResources(colorPalettesResourcePrefix);
    for (auto const & resourceName : colorPaletteResourceNames) {
    
        auto res = ResourceDB::getResource(resourceName);
        if (res) {
    
            ResourcePointer palette{new ColorPalette{QString::null, res->getData()}};
            if (palette->isValid() && !palette->getName().isEmpty()) {
                palettes.emplace(palette->getName(), palette);
                ui->paletteBox->addItem(palette->getName());
            }
        }
    }
    
    selectedPaletteChanged();
}


void ColorChooserWidget::pickColor() {

    auto color = QColorDialog::getColor(Qt::white, this);
    if (!color.isValid()) {
        return;
    }
    ui->recentColorsWidget->addColor(color);
    ui->recentColorsWidget->selectedColorChange(0, true);
}


void ColorChooserWidget::saveCurrentPaletteToFile(QString filename) {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    
    auto palette = (*iter).second;
    auto colorPalette = dynamic_cast<ColorPalette *>(palette.data());
    if (!colorPalette) {
        throw std::runtime_error{"Not a color palette resource pointer present, when expected."};
    }
    auto json = colorPalette->toJSON();
    
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
    
    lastFolderUsed = QFileInfo{file}.dir().absolutePath();
}


void ColorChooserWidget::savePalette() {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    
    auto answer = savePaletteDialog->exec();
    if ((answer == 0) || savePaletteDialog->selectedFiles().empty()) {
        return;
    }
    saveCurrentPaletteToFile(savePaletteDialog->selectedFiles().first());
}


void ColorChooserWidget::selectedPaletteChanged() {
    
    auto iter = palettes.find(ui->paletteBox->currentText());
    if (iter == palettes.end()) {
        return;
    }
    ui->scrollAreaWidgetContents->setPalette((*iter).second);
}


void ColorChooserWidget::setLastFolderUsed(QString folder) {
    
    QFileInfo fileInfo{folder};
    if (fileInfo.exists() && fileInfo.isDir()) {
        lastFolderUsed = folder;
        loadPaletteDialog->setDirectory(lastFolderUsed);
        savePaletteDialog->setDirectory(lastFolderUsed);
    }
}


QString ColorChooserWidget::suggestNewName(QString const & name) const {
    
    QStringList knownNames;
    for (int i = 0; i < ui->paletteBox->count(); ++i) {
        knownNames.append(ui->paletteBox->itemText(i));
    }
    
    int newIndex = 0;
    QString newName;
    bool found = false;
    do {
        ++newIndex;
        newName = name + QString("_%1").arg(newIndex);
        found = !knownNames.contains(newName);
    } while (!found);
    
    return newName;
}

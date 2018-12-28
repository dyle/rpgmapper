/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QAbstractSlider>
#include <QFontMetrics>

#include "zoomslider.hpp"
#include "ui_zoomslider.h"

using namespace rpgmapper::view;


std::vector<int> const ZoomSlider::zoomTable = {
    16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
    64, 68, 72, 76, 80, 86, 92, 96, 100, 104, 108, 112,
    116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156,
    160, 164, 166, 172, 176, 180, 184, 188, 192
};


std::map<int, int> ZoomSlider::sizeTable;


ZoomSlider::ZoomSlider(QWidget *parent) : QWidget{parent} {
    
    initZoomTable();
    
    ui = std::make_shared<Ui_ZoomSlider>();
    ui->setupUi(this);
    
    ui->zoomSlider->setMinimum(0);
    ui->zoomSlider->setMaximum(zoomTable.size() - 1);
    
    QFontMetrics fontMetrics(font());
    ui->zoomValue->setMinimumSize(fontMetrics.tightBoundingRect("XXXX").size());
    ui->zoomValue->setText(QString::null);
    
    connect(ui->zoomSlider, &QAbstractSlider::valueChanged, this, &ZoomSlider::sliderChanged);
}


void ZoomSlider::decrease() {
    
    int currentZoom = ui->zoomSlider->value();
    if (currentZoom > 0) {
        setTileSize(zoomTable[currentZoom - 1]);
    }
}


int ZoomSlider::getTileSize() const {
    return zoomTable.at(ui->zoomSlider->value());
}


void ZoomSlider::increase() {
    int currentZoom = ui->zoomSlider->value();
    if (static_cast<unsigned int>(currentZoom) < (zoomTable.size() - 1)) {
        setTileSize(zoomTable[currentZoom + 1]);
    }
}


void ZoomSlider::initZoomTable() const {

    static bool initialized = false;
    
    if (!initialized) {
        initialized = true;
        for (int i = 0; i < static_cast<int>(zoomTable.size()); ++i) {
            sizeTable.emplace(zoomTable[i], i);
        }
    }
}


bool ZoomSlider::isZoomInPossible() const {
    return ui->zoomSlider->value() < ui->zoomSlider->maximum();
}


bool ZoomSlider::isZoomOutPossible() const {
    return ui->zoomSlider->value() > ui->zoomSlider->minimum();
}


void ZoomSlider::setTileSize(int tileSize) {
    
    auto iter = sizeTable.find(tileSize);
    if (iter == sizeTable.end()) {
        return;
    }
    
    auto value = (*iter).second;
    if (value != ui->zoomSlider->value()) {
        ui->zoomSlider->setValue(value);
        ui->zoomValue->setText(QString::number(tileSize));
    }
}


void ZoomSlider::sliderChanged() {
    
    auto tileSize = zoomTable.at(ui->zoomSlider->value());
    ui->zoomValue->setText(QString::number(tileSize));
    emit zoomChanged(tileSize);
}

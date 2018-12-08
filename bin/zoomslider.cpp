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


std::vector<int> const ZoomSlider::zoomTable = {16, 24, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192};


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

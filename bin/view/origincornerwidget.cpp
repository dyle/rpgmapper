/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

// rpgmapper
#include "origincornerwidget.hpp"
#include "ui_origincornerwidget.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent         parent widget instance
 */
OriginCornerWidget::OriginCornerWidget(QWidget * cParent) : QWidget{cParent} {
    ui = std::make_shared<Ui_origincornerwidget>();
    ui->setupUi(this);
}


/**
 * Get the current selected corner.
 *
 * @return  the current selected corner
 */
rpgmapper::model::Map::map_corner OriginCornerWidget::corner() const {

    if (ui->rbBottomLeft->isChecked()) {
        return Map::map_corner::bottomLeft;
    }
    if (ui->rbBottomRight->isChecked()) {
        return Map::map_corner::bottomRight;
    }
    if (ui->rbTopLeft->isChecked()) {
        return Map::map_corner::topLeft;
    }
    if (ui->rbTopRight->isChecked()) {
        return Map::map_corner::topRight;
    }

    throw std::runtime_error("Unknown state for map's origin corner.");
}


/**
 * Set the active corner.
 *
 * @param   eCorner     the current active corner
 */
void OriginCornerWidget::setCorner(rpgmapper::model::Map::map_corner eCorner) {

    ui->rbBottomLeft->setChecked(false);
    ui->rbBottomRight->setChecked(false);
    ui->rbTopLeft->setChecked(false);
    ui->rbTopRight->setChecked(false);

    switch (eCorner){
        case Map::map_corner::bottomLeft:
            ui->rbBottomLeft->setChecked(true);
            break;
        case Map::map_corner::bottomRight:
            ui->rbBottomRight->setChecked(true);
            break;
        case Map::map_corner::topLeft:
            ui->rbTopLeft->setChecked(true);
            break;
        case Map::map_corner::topRight:
            ui->rbTopRight->setChecked(true);
            break;
    }
}

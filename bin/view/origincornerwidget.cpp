/*
 * origincornerwidget.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

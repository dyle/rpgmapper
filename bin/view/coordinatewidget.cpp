/*
 * coordinateWidget.cpp
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
#include "coordinatewidget.hpp"
#include "ui_coordinatewidget.h"

using namespace rpgmapper::view;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent         parent widget instance
 */
CoordinateWidget::CoordinateWidget(QWidget * cParent) : QWidget{cParent} {

    ui = std::make_shared<Ui_coordinatewidget>();
    ui->setupUi(this);

    QFontMetrics cFM(font());
    auto cRect = cFM.boundingRect("XXXX");
    ui->lblXValue->setMinimumSize(cRect.size());
    ui->lblYValue->setMinimumSize(cRect.size());

    clear();
}


/**
 * Clears the coordinate display.
 */
void CoordinateWidget::clear() {
    showCoordinates("", "");
}


/**
 * Display some coordinates.
 *
 * @param   sXCoordinate        the X coordinate in user dimensions
 * @param   sYCoordinate        the Y coordinate in user dimensions
 */
void CoordinateWidget::showCoordinates(QString sXCoordinate, QString sYCoordinate) {
    ui->lblXValue->setText(sXCoordinate);
    ui->lblYValue->setText(sYCoordinate);
}

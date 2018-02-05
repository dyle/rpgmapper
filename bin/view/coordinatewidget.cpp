/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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

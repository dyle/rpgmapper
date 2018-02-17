/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "coordinateswidget.hpp"
#include "ui_coordinateswidget.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


CoordinatesWidget::CoordinatesWidget(QWidget * parent) : QWidget{parent} {

    ui = std::make_shared<Ui_coordinatesWidget>();
    ui->setupUi(this);

    QFontMetrics fontMetrics(font());
    auto rect = fontMetrics.boundingRect("XXXX");
    ui->xValueLabel->setMinimumSize(rect.size());
    ui->yValueLabel->setMinimumSize(rect.size());

    clear();
}


void CoordinatesWidget::clear() {
    ui->xValueLabel->setText(QString::null);
    ui->yValueLabel->setText(QString::null);
}


void CoordinatesWidget::showCoordinates(NumeralCoordinates const & coordinates) {
    ui->xValueLabel->setText(coordinates.x);
    ui->yValueLabel->setText(coordinates.y);
}

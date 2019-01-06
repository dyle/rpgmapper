/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include "coordinatesoriginwidget.hpp"
#include "ui_coordinatesoriginwidget.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


CoordinatesOriginWidget::CoordinatesOriginWidget(QWidget * parent) : QWidget{parent} {
    ui = std::make_shared<Ui_coordinatesOriginWidget>();
    ui->setupUi(this);
}


CoordinatesOrigin CoordinatesOriginWidget::getOrigin() const {

    if (ui->bottomLeftRadioButton->isChecked()) {
        return CoordinatesOrigin::bottomLeft;
    }
    if (ui->bottomRightRadioButton->isChecked()) {
        return CoordinatesOrigin::bottomRight;
    }
    if (ui->topLeftRadioButton->isChecked()) {
        return CoordinatesOrigin::topLeft;
    }
    if (ui->topRightRadioButton->isChecked()) {
        return CoordinatesOrigin::topRight;
    }

    throw std::runtime_error("Unknown state for map's origin corner.");
}


void CoordinatesOriginWidget::setOrigin(CoordinatesOrigin origin) {

    ui->bottomLeftRadioButton->setChecked(false);
    ui->bottomRightRadioButton->setChecked(false);
    ui->topLeftRadioButton->setChecked(false);
    ui->topRightRadioButton->setChecked(false);

    switch (origin){

        case CoordinatesOrigin::bottomLeft:
            ui->bottomLeftRadioButton->setChecked(true);
            break;

        case CoordinatesOrigin::bottomRight:
            ui->bottomRightRadioButton->setChecked(true);
            break;

        case CoordinatesOrigin::topLeft:
            ui->topLeftRadioButton->setChecked(true);
            break;

        case CoordinatesOrigin::topRight:
            ui->topRightRadioButton->setChecked(true);
            break;
    }
}

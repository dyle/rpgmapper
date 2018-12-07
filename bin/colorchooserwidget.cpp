/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include "colorchooserwidget.hpp"
#include "ui_colorchooserwidget.h"

using namespace rpgmapper::view;


ColorChooserWidget::ColorChooserWidget(QWidget * parent) : QWidget{parent} {
    ui = std::make_shared<Ui_ColorChooserWidget>();
    ui->setupUi(this);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include "aboutdialog.hpp"
#include "ui_aboutdialog.h"

using namespace rpgmapper::view;


AboutDialog::AboutDialog(QWidget * parent) : QDialog{parent} {
    ui = std::make_shared<Ui_aboutDialog>();
    ui->setupUi(this);
}

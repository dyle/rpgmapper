/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include "resourcesviewdialog.hpp"
#include "ui_resourcesviewdialog.h"

using namespace rpgmapper::view;


ResourcesViewDialog::ResourcesViewDialog(QWidget * parent) : QDialog{parent} {
    ui = std::make_shared<Ui_resourcesViewDialog>();
    ui->setupUi(this);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

// rpgmapper
#include "aboutdialog.hpp"
#include "ui_aboutdialog.h"

using namespace rpgmapper::view;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent         parent widget instance
 */
AboutDialog::AboutDialog(QWidget * cParent) : QDialog{cParent} {
    ui = std::make_shared<Ui_aboutdialog>();
    ui->setupUi(this);
}

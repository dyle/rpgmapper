/*
 * atlas_properties_dialog.cpp
 *
 * Show and modify atlas properties
 * 
 * Copyright (C) 2015, Oliver Maurhart, <dyle@dyle.org>
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
#include "model/atlas.h"
#include "view/atlas_properties_dialog.h"

#include "ui_atlas_properties_dialog.h"


// ------------------------------------------------------------
// code


/**
 * ctor
 *
 * @param   sTitle      title of the dialog
 * @param   sText       additional text to set
 */
atlas_properties_dialog::atlas_properties_dialog(QString const & sTitle, QString const & sText) : QDialog() {
    
    ui = new Ui_atlas_properties_dialog;
    ui->setupUi(this);

    setWindowTitle(sTitle);
    ui->lblText->setText(sText);

    // widget connectors
    connect(ui->btnCancel, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->btnOk, SIGNAL(clicked()), SLOT(accept()));
    connect(ui->wdAtlasProperties, SIGNAL(changed()), SLOT(atlas_properties_changed()));
}


/**
 * dtor
 */
atlas_properties_dialog::~atlas_properties_dialog() {
    delete ui;
}


/**
 * atlas properties have changed
 */
void atlas_properties_dialog::atlas_properties_changed() {
    ui->btnOk->setEnabled(ui->wdAtlasProperties->valid());
}


/**
 * clear the dialog
 */
void atlas_properties_dialog::clear() {
    ui->wdAtlasProperties->clear();
}


/**
 * evaluate current main window state
 */
void atlas_properties_dialog::evaluate() {
}


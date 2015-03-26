/*
 * atlas_properties_widget.cpp
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
#include "view/atlas_properties_widget.h"

#include "ui_atlas_properties_widget.h"

// ------------------------------------------------------------
// code


/**
 * ctor
 *
 * @param   cParent     parent widget
 */
atlas_properties_widget::atlas_properties_widget(QWidget * cParent) : QWidget(cParent) {

    ui = new Ui_atlas_properties_widget;
    ui->setupUi(this);

    // connect widgets
    connect(ui->edtAtlasName, SIGNAL(textChanged(const QString&)), SIGNAL(changed()));
    connect(ui->edtAtlasDescription, SIGNAL(textChanged(const QString&)), SIGNAL(changed()));

    // TODO: work on atlas picture
}


/**
 * dtor
 */
atlas_properties_widget::~atlas_properties_widget() {
    delete ui;
}


/**
 * clear all widget data
 */
void atlas_properties_widget::clear() {
    ui->edtAtlasName->clear();
    ui->edtAtlasDescription->clear();
    // TODO: clear atlas picture

}


/**
 * check if the current widget data represents a valid atlas
 *
 * @return  true, if we have valid atlas data
 */
bool atlas_properties_widget::valid() {
    // TODO: calculate atlas validity
    return false;
}


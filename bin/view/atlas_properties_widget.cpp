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

// Qt
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QMessageBox>

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
    m_cLblPicture = new QLabel;
    ui->scrPicture->setWidget(m_cLblPicture);

    m_cFileDialog = new QFileDialog(this, tr("Select atlas image"));
    m_cFileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    m_cFileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList sFilerList;
    sFilerList << tr("Image files (*.png *.xpm *.jpg)") << tr("All files (*)");
    m_cFileDialog->setNameFilters(sFilerList);

    // connect widgets
    connect(ui->edtAtlasName, SIGNAL(textChanged(const QString&)), SIGNAL(changed()));
    connect(ui->edtAtlasDescription, SIGNAL(textChanged(const QString&)), SIGNAL(changed()));
    connect(ui->btnFileOpen, SIGNAL(clicked()), SLOT(select_image_file()));
}


/**
 * dtor
 */
atlas_properties_widget::~atlas_properties_widget() {
    delete m_cFileDialog;
    delete ui;
}


/**
 * clear all widget data
 */
void atlas_properties_widget::clear() {
    ui->edtAtlasName->clear();
    ui->edtAtlasDescription->clear();
    m_cLblPicture->setPixmap(QPixmap());
}


/**
 * let the user select an image file
 */
void atlas_properties_widget::select_image_file() {

    if (m_cFileDialog->exec() == QDialog::Rejected) return;
    QStringList sFiles = m_cFileDialog->selectedFiles();
    if (sFiles.count() == 0) return;
    QString sFile = sFiles.at(0);

    // try to load as image
    QImage cImage = QImage(sFile);
    if (cImage.isNull()) {
        QMessageBox::critical(this, tr("Failed to load image"), QString(tr("Failed to load image file at %1.\nIs this file an image?").arg(sFile)));
        return;
    }

    // set image and filename
    m_cLblPicture->setPixmap(QPixmap::fromImage(cImage));
    ui->edtFileOpen->setText(sFile);

    emit changed();
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


/*
 * mappropertiesdialog.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
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
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>
#include "mappropertiesdialog.hpp"
#include "ui_mappropertiesdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent         parent widget instance
 */
MapPropertiesDialog::MapPropertiesDialog(QWidget * cParent) : QDialog{cParent} {

    ui = std::make_shared<Ui_mappropertiesdialog>();
    ui->setupUi(this);

    connect(ui->sbWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::widthChanged);
    connect(ui->sbHeight, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::heightChanged);
}


/**
 * Evaluate all widgets anew.
 */
void MapPropertiesDialog::evaluate() {

    reset();
    if (m_cMap.data() == nullptr) {
        return;
    }

    ui->edtName->setText(m_cMap->name());

    ui->sbWidth->setValue(m_cMap->size().width());
    ui->sbHeight->setValue(m_cMap->size().height());
    ui->sbResizeOffsetX->setValue(m_cMap->originOffset().x());
    ui->sbResizeOffsetY->setValue(m_cMap->originOffset().x());

    ui->wdOriginCornerWidget->setCorner(m_cMap->originCorner());

    // TODO
    ui->rbNumericalX->setChecked(true);
    ui->sbStartXValue->setValue(0);

    // TODO
    ui->rbNumericalY->setChecked(true);
    ui->sbStartYValue->setValue(0);
}


/**
 * The height value changed.
 *
 * @param   nValue      the new value
 */
void MapPropertiesDialog::heightChanged(int nValue) {
    if (ui->tbLinkSize->isChecked() && (ui->sbWidth->value() != nValue)) {
        ui->sbWidth->setValue(nValue);
    }
}


/**
 * Reset all widgets to an initial state.
 */
void MapPropertiesDialog::reset() {

    ui->edtName->clear();

    ui->sbWidth->setValue(1);
    ui->sbHeight->setValue(1);
    ui->sbResizeOffsetX->setValue(0);
    ui->sbResizeOffsetY->setValue(0);

    ui->wdOriginCornerWidget->setCorner(Map::map_corner::bottomLeft);

    ui->rbNumericalX->setChecked(true);
    ui->sbStartXValue->setValue(0);
    ui->edtAxisXSample->clear();

    ui->rbNumericalY->setChecked(true);
    ui->sbStartYValue->setValue(0);
    ui->edtAxisYSample->clear();
}


/**
 * Set the map to be configured.
 *
 * @param   cMap        the map to be configured
 */
void MapPropertiesDialog::setMap(rpgmapper::model::MapPointer & cMap) {
    m_cMap = cMap;
    evaluate();
}


/**
 * The width value changed.
 *
 * @param   nValue      the new value
 */
void MapPropertiesDialog::widthChanged(int nValue) {
    if (ui->tbLinkSize->isChecked() && (ui->sbHeight->value() != nValue)) {
        ui->sbHeight->setValue(nValue);
    }
}

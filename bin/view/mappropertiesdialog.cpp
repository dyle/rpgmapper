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

#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>
#include <rpgmapper/layer.hpp>
#include "mappropertiesdialog.hpp"
#include "ui_mappropertiesdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl


/**
 * Unit converters for the example axis units.
 */
static struct {

    /**
     * Alphabetical big caps unit converter.
     */
    QSharedPointer<rpgmapper::model::UnitConverter> m_cAlphabeticalBigCaps;

    /**
     * Alphabetical small caps unit converter.
     */
    QSharedPointer<rpgmapper::model::UnitConverter> m_cAlphabeticalSmallCaps;

    /**
     * Alphabetical big caps unit converter.
     */
    QSharedPointer<rpgmapper::model::UnitConverter> m_cNumerical;

    /**
     * Alphabetical big caps unit converter.
     */
    QSharedPointer<rpgmapper::model::UnitConverter> m_cRoman;

} g_cUnitConverters;


/**
 * Init the unit converters.
 */
static void initConverters();


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

    m_cBackgroundPreview = new QLabel{this};
    m_cBackgroundPreview->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_cBackgroundPreview->setScaledContents(false);
    ui->saImage->setWidget(m_cBackgroundPreview);

    connect(ui->sbWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::widthChanged);
    connect(ui->sbHeight, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::heightChanged);

    connect(ui->rbAlphaBigX, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->rbAlphaSmallX, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->rbNumericalX, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->rbRomanX, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->sbStartXValue, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::showSampleXAxis);

    connect(ui->rbAlphaBigY, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->rbAlphaSmallY, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->rbNumericalY, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->rbRomanY, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->sbStartYValue, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::showSampleYAxis);

    connect(ui->tbFontAxis, &QToolButton::clicked, this, &MapPropertiesDialog::selectAxisFont);
    connect(ui->tbAxisColor, &QToolButton::clicked, this, &MapPropertiesDialog::selectAxisColor);

    connect(ui->tbBackgroundColorPick, &QToolButton::clicked, this, &MapPropertiesDialog::selectBackgroundColor);
    connect(ui->tbImageFile, &QToolButton::clicked, this, &MapPropertiesDialog::selectBackgroundImage);
    connect(ui->rbBackgroundImagePlain, &QRadioButton::clicked,
            this, &MapPropertiesDialog::setBackgroundImageRenderMode);
    connect(ui->rbBackgroundImageScaled, &QRadioButton::clicked,
            this, &MapPropertiesDialog::setBackgroundImageRenderMode);
    connect(ui->rbBackgroundImageTiled, &QRadioButton::clicked,
            this, &MapPropertiesDialog::setBackgroundImageRenderMode);
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

    // Dimension tab
    ui->sbWidth->setValue(m_cMap->size().width());
    ui->sbHeight->setValue(m_cMap->size().height());
    ui->wdOriginCornerWidget->setCorner(m_cMap->originCorner());

    // Axis tab
    ui->rbNumericalX->setChecked(true);
    ui->sbStartXValue->setValue(0);
    ui->edtAxisXSample->setFont(m_cAxisFont);
    ui->rbNumericalY->setChecked(true);
    ui->sbStartYValue->setValue(0);
    ui->edtAxisYSample->setFont(m_cAxisFont);
    ui->edtFontAxis->setText(m_cAxisFont.family() + ", " + QString::number(m_cAxisFont.pointSize()) + "pt");
    ui->edtFontAxis->setCursorPosition(0);
    auto cAxisPalette = ui->frAxisColor->palette();
    cAxisPalette.setColor(QPalette::Window, m_cAxisColor);
    ui->frAxisColor->setPalette(cAxisPalette);
    showSampleXAxis();
    showSampleYAxis();

    // Background tab
    auto cBackgroundPalette = ui->frBackgroundColor->palette();
    cBackgroundPalette.setColor(QPalette::Window, m_cBackgroundColor);
    ui->frBackgroundColor->setPalette(cBackgroundPalette);
    ui->edtImageFile->setText(m_sImageFile);
    ui->edtImageFile->setCursorPosition(0);
    Map::map_background_image_render_mode eRenderMode = Map::map_background_image_render_mode::plain;
    if (ui->rbBackgroundImageScaled->isChecked()) {
        eRenderMode = Map::map_background_image_render_mode::scaled;
    }
    if (ui->rbBackgroundImageTiled->isChecked()) {
        eRenderMode = Map::map_background_image_render_mode::tiled;
    }
    switch (eRenderMode) {

        case Map::map_background_image_render_mode::plain:
            m_cBackgroundPreview->setScaledContents(false);
            break;

        case Map::map_background_image_render_mode::scaled:
            m_cBackgroundPreview->setScaledContents(true);
            break;

        case Map::map_background_image_render_mode::tiled:
            // TODO
            break;
    }
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

    ui->wdOriginCornerWidget->setCorner(Map::map_corner::bottomLeft);

    ui->rbNumericalX->setChecked(true);
    ui->sbStartXValue->setValue(0);
    ui->edtAxisXSample->clear();

    ui->rbNumericalY->setChecked(true);
    ui->sbStartYValue->setValue(0);
    ui->edtAxisYSample->clear();

    ui->rbBackgroundColor->setChecked(true);
    ui->rbBackgroundImagePlain->setChecked(true);
}


/**
 * Select a color for the axis.
 */
void MapPropertiesDialog::selectAxisColor() {

    QColor cColor = QColorDialog::getColor(m_cAxisColor, this);
    if (cColor.isValid()) {
        m_cAxisColor = cColor;
        evaluate();
    }
}


/**
 * Select a font for the axis.
 */
void MapPropertiesDialog::selectAxisFont() {

    bool bOk = false;
    QFont cFont = QFontDialog::getFont(&bOk, m_cAxisFont, this);
    if (bOk) {
        m_cAxisFont = cFont.toString();
        evaluate();
    }
}


/**
 * Select a color for the background.
 */
void MapPropertiesDialog::selectBackgroundColor() {

    QColor cColor = QColorDialog::getColor(m_cBackgroundColor, this);
    if (cColor.isValid()) {
        m_cBackgroundColor = cColor;
        evaluate();
    }
}


/**
 * Select a image for the background.
 */
void MapPropertiesDialog::selectBackgroundImage() {

    auto sFileName = QFileDialog::getOpenFileName(this, tr("Pick an image as map background"));
    QImage cBackgroundImage{sFileName};
    if (cBackgroundImage.isNull()) {
        QString sMessage = QString{tr("Failed to load image '%1'\nIs this an image?")}.arg(sFileName);
        QMessageBox::critical(this, tr("Failed to load image."), sMessage);
        return;
    }

    m_sImageFile = sFileName;
    m_cBackgroundImage = cBackgroundImage;

    QPixmap cBackgroundPixmap;
    if (cBackgroundPixmap.convertFromImage(m_cBackgroundImage)) {
        m_cBackgroundPreview->setPixmap(cBackgroundPixmap);
        m_cBackgroundPreview->resize(m_cBackgroundPreview->pixmap()->size());
    }
    else {
        QString sMessage = QString{tr("Failed to apply image '%1'.\n")}.arg(sFileName);
        QMessageBox::critical(this, tr("Failed to set image."), sMessage);
    }

    evaluate();
}


/**
 * The background image render mode changed.
 */
void MapPropertiesDialog::setBackgroundImageRenderMode() {
    evaluate();
}


/**
 * Set the map to be configured.
 *
 * @param   cMap        the map to be configured
 */
void MapPropertiesDialog::setMap(rpgmapper::model::MapPointer & cMap) {

    m_cMap = cMap;
    m_cAxisFont.fromString(m_cMap->gridLayer()->attributes()["font"]);
    m_cAxisColor = QColor(m_cMap->gridLayer()->attributes()["color"]);
    m_cBackgroundColor = QColor(m_cMap->backgroundLayer()->attributes()["color"]);

    evaluate();
}


/**
 * Show examples for units on the X Axis.
 */
void MapPropertiesDialog::showSampleXAxis() {

    initConverters();

    QSharedPointer<rpgmapper::model::UnitConverter> cConverter;
    if (ui->rbAlphaBigX->isChecked()) {
        cConverter = g_cUnitConverters.m_cAlphabeticalBigCaps;
    }
    if (ui->rbAlphaSmallX->isChecked()) {
        cConverter = g_cUnitConverters.m_cAlphabeticalSmallCaps;
    }
    if (ui->rbNumericalX->isChecked()) {
        cConverter = g_cUnitConverters.m_cNumerical;
    }
    if (ui->rbRomanX->isChecked()) {
        cConverter = g_cUnitConverters.m_cRoman;
    }

    if (cConverter.data() == nullptr) {
        throw std::runtime_error("Cannot deduce unit converter for current option on X axis.");
    }

    QStringList cExamples;
    for (int i = 0; i < 7; ++i) {
        cExamples << cConverter->convert(i + ui->sbStartXValue->value());
    }
    ui->edtAxisXSample->setText(cExamples.join(",") + ", ...");
    ui->edtAxisXSample->setCursorPosition(0);
}


/**
 * Show examples for units on the Y Axis.
 */
void MapPropertiesDialog::showSampleYAxis() {

    initConverters();

    QSharedPointer<rpgmapper::model::UnitConverter> cConverter;
    if (ui->rbAlphaBigY->isChecked()) {
        cConverter = g_cUnitConverters.m_cAlphabeticalBigCaps;
    }
    if (ui->rbAlphaSmallY->isChecked()) {
        cConverter = g_cUnitConverters.m_cAlphabeticalSmallCaps;
    }
    if (ui->rbNumericalY->isChecked()) {
        cConverter = g_cUnitConverters.m_cNumerical;
    }
    if (ui->rbRomanY->isChecked()) {
        cConverter = g_cUnitConverters.m_cRoman;
    }

    if (cConverter.data() == nullptr) {
        throw std::runtime_error("Cannot deduce unit converter for current option on Y axis.");
    }

    QStringList cExamples;
    for (int i = 0; i < 7; ++i) {
        cExamples << cConverter->convert(i + ui->sbStartYValue->value());
    }
    ui->edtAxisYSample->setText(cExamples.join(",") + ", ...");
    ui->edtAxisYSample->setCursorPosition(0);
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


/**
 * Init the unit converters.
 */
void initConverters() {

    if (g_cUnitConverters.m_cAlphabeticalBigCaps.data() == nullptr) {
        g_cUnitConverters.m_cAlphabeticalBigCaps = UnitConverter::create(UnitConverter::alphabeticalBigCaps);
    }

    if (g_cUnitConverters.m_cAlphabeticalSmallCaps.data() == nullptr) {
        g_cUnitConverters.m_cAlphabeticalSmallCaps = UnitConverter::create(UnitConverter::alphabeticalSmallCaps);
    }

    if (g_cUnitConverters.m_cNumerical.data() == nullptr) {
        g_cUnitConverters.m_cNumerical = UnitConverter::create(UnitConverter::numeric);
    }

    if (g_cUnitConverters.m_cRoman.data() == nullptr) {
        g_cUnitConverters.m_cRoman = UnitConverter::create(UnitConverter::roman);
    }
}

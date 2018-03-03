/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/command/composite_command.hpp>
#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_origin.hpp>
#include "mappropertiesdialog.hpp"
#include "ui_mappropertiesdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;
using namespace rpgmapper::view;


MapPropertiesDialog::MapPropertiesDialog(QWidget * parent) : QDialog{parent} {

    ui = std::make_shared<Ui_mapPropertiesDialog>();
    ui->setupUi(this);

    initNumeralConverters();

    backgroundPreviewLabel = new QLabel{this};
    backgroundPreviewLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    backgroundPreviewLabel->setScaledContents(false);
    ui->backgroundImageScrollArea->setWidget(backgroundPreviewLabel);

    connect(ui->widthSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::widthChanged);
    connect(ui->heightSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::heightChanged);

    connect(ui->xAlphaBigRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->xAlphaSmallRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->xNumericalRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->xRomanRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleXAxis);
    connect(ui->xStartValueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::showSampleXAxis);

    connect(ui->yAlphaBigRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->yAlphaSmallRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->yNumericalRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->yRomanRadioButton, &QRadioButton::clicked, this, &MapPropertiesDialog::showSampleYAxis);
    connect(ui->yStartValueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::showSampleYAxis);

    connect(ui->axisFontToolButton, &QToolButton::clicked, this, &MapPropertiesDialog::selectAxisFont);
    connect(ui->axisColorToolButton, &QToolButton::clicked, this, &MapPropertiesDialog::selectAxisColor);

    connect(ui->backgroundColorToolButton, &QToolButton::clicked,
            this, &MapPropertiesDialog::selectBackgroundColor);
    connect(ui->backgroundImageFileToolButton, &QToolButton::clicked,
            this, &MapPropertiesDialog::selectBackgroundImage);
    connect(ui->backgroundImagePlainRadioButton, &QRadioButton::clicked,
            this, &MapPropertiesDialog::setBackgroundImageRenderMode);
    connect(ui->backgroundImageScaledRadioButton, &QRadioButton::clicked,
            this, &MapPropertiesDialog::setBackgroundImageRenderMode);
    connect(ui->backgroundImageTiledRadioButton, &QRadioButton::clicked,
            this, &MapPropertiesDialog::setBackgroundImageRenderMode);

    connect(ui->okButton, &QPushButton::clicked, this, &MapPropertiesDialog::clickedOk);
}


void MapPropertiesDialog::applyDimensionValuesToMap(CompositeCommand * & commands) {

    auto atlas = this->atlas.toStrongRef();
    if (atlas == nullptr) {
        throw std::runtime_error("Atlas instance in properties vanished (nullptr).");
    }

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Internal map lost when applying values of property dialog (map == nullptr).");
    }

    auto newWidth = ui->widthSpinBox->value();
    auto newHeight = ui->heightSpinBox->value();
    auto mapSize = map->getSize();
    if ((mapSize.width() != newWidth) || (mapSize.height() != newHeight)) {
        commands->addCommand(CommandPointer{new ResizeMap{atlas, map->getName(), QSize{newWidth, newHeight}}});
    }

    auto origin = ui->coordinatesOriginWidget->getOrigin();
    if (origin != map->getCoordinateSystem().getOrigin()) {
        commands->addCommand(CommandPointer{new SetMapOrigin{atlas, map->getName(), origin}});
    }
}


void MapPropertiesDialog::applyValuesToMap() {

    auto atlas = this->atlas.toStrongRef();
    if (atlas == nullptr) {
        throw std::runtime_error("Atlas instance in properties vanished (nullptr).");
    }

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

    auto commands = new CompositeCommand{atlas};
    if (ui->nameEdit->text() != map->getName()) {
        // TODO: check for invalid characters
        commands->addCommand(CommandPointer{new SetMapName(atlas, map->getName(), ui->nameEdit->text())});
    }

    applyDimensionValuesToMap(commands);
    // TODO: add axis values
    // TODO: add background values

    atlas->getCommandProzessor()->execute(CommandPointer{commands});
}


void MapPropertiesDialog::clickedOk() {
    applyValuesToMap();
    accept();
}


void MapPropertiesDialog::evaluate() {

    auto map = this->map.toStrongRef();
    if (map.data() == nullptr) {
        return;
    }

    ui->nameEdit->setText(map->getName());
/*
    // Dimension tab
    ui->widthSpinBox->setValue(map->getSize().width());
    ui->heightSpinBox->setValue(map->getSize().height());
    ui->wdOriginCornerWidget->setCorner(map->originCorner());

    // Axis tab
    ui->xNumericalRadioButton->setChecked(true);
    ui->xStartValueSpinBox->setValue(0);
    ui->edtAxisXSample->setFont(axisFont);
    ui->yNumericalRadioButton->setChecked(true);
    ui->yStartValueSpinBox->setValue(0);
    ui->edtAxisYSample->setFont(axisFont);
    ui->edtFontAxis->setText(axisFont.family() + ", " + QString::number(axisFont.pointSize()) + "pt");
    ui->edtFontAxis->setCursorPosition(0);
    auto cAxisPalette = ui->frAxisColor->palette();
    cAxisPalette.setColor(QPalette::Window, axisColor);
    ui->frAxisColor->setPalette(cAxisPalette);
    showSampleXAxis();
    showSampleYAxis();

    // Background tab
    auto cBackgroundPalette = ui->frBackgroundColor->palette();
    cBackgroundPalette.setColor(QPalette::Window, backgroundColor);
    ui->frBackgroundColor->setPalette(cBackgroundPalette);
    ui->edtImageFile->setText(m_sImageFile);
    ui->edtImageFile->setCursorPosition(0);
    Map::map_background_image_render_mode eRenderMode = Map::map_background_image_render_mode::plain;
    if (ui->backgroundImageScaledRadioButton->isChecked()) {
        eRenderMode = Map::map_background_image_render_mode::scaled;
    }
    if (ui->backgroundImageTiledRadioButton->isChecked()) {
        eRenderMode = Map::map_background_image_render_mode::tiled;
    }
    switch (eRenderMode) {

        case Map::map_background_image_render_mode::plain:
            backgroundPreviewLabel->setScaledContents(false);
            break;

        case Map::map_background_image_render_mode::scaled:
            backgroundPreviewLabel->setScaledContents(true);
            break;

        case Map::map_background_image_render_mode::tiled:
            // TODO
            break;
    }
*/
}


void MapPropertiesDialog::heightChanged(int value) {
    if (ui->linkWidthHeightToolButton->isChecked() && (ui->widthSpinBox->value() != value)) {
        ui->widthSpinBox->setValue(value);
    }
}


void MapPropertiesDialog::selectAxisColor() {

    QColor color = QColorDialog::getColor(axisColor, this);
    if (color.isValid()) {
        axisColor = color;
        evaluate();
    }
}


void MapPropertiesDialog::selectAxisFont() {

    bool ok = false;
    QFont cFont = QFontDialog::getFont(&ok, axisFont, this);
    if (ok) {
        axisFont = cFont.toString();
        evaluate();
    }
}


void MapPropertiesDialog::selectBackgroundColor() {

    QColor color = QColorDialog::getColor(backgroundColor, this);
    if (color.isValid()) {
        backgroundColor = color;
        evaluate();
    }
}


void MapPropertiesDialog::selectBackgroundImage() {

    auto fileName = QFileDialog::getOpenFileName(this, tr("Pick an image as map background"));
    QImage backgroundImage{fileName};
    if (backgroundImage.isNull()) {
        QString message = QString{tr("Failed to load image '%1'\nIs this an image?")}.arg(fileName);
        QMessageBox::critical(this, tr("Failed to load image."), message);
        return;
    }

    backgroundImageFileName = fileName;
    this->backgroundImage = backgroundImage;

    QPixmap backgroundPixmap;
    if (backgroundPixmap.convertFromImage(this->backgroundImage)) {
        backgroundPreviewLabel->setPixmap(backgroundPixmap);
        backgroundPreviewLabel->resize(backgroundPreviewLabel->pixmap()->size());
    }
    else {
        QString message = QString{tr("Failed to apply image '%1'.\n")}.arg(fileName);
        QMessageBox::critical(this, tr("Failed to set image."), message);
    }

    evaluate();
}


void MapPropertiesDialog::setAxisUiFromMap() {

    // TODO: check with map settings

    ui->xNumericalRadioButton->setChecked(true);
    ui->xAlphaSmallRadioButton->setChecked(false);
    ui->xAlphaBigRadioButton->setChecked(false);
    ui->xRomanRadioButton->setChecked(false);
    ui->xStartValueSpinBox->setValue(0);

    ui->yNumericalRadioButton->setChecked(true);
    ui->yAlphaSmallRadioButton->setChecked(false);
    ui->yAlphaBigRadioButton->setChecked(false);
    ui->yRomanRadioButton->setChecked(false);
    ui->yStartValueSpinBox->setValue(0);

    ui->axisFontLineEdit->setText(font().toString());
    //ui->axisColorFrame->setBackgroundColor();
//    axisFont.fromString(this->map->gridLayer()->attributes()["font"]);
//    axisColor = QColor(map->gridLayer()->attributes()["color"]);
}


void MapPropertiesDialog::setBackgroundImageRenderMode() {
    evaluate();
}


void MapPropertiesDialog::setBackgroundUiFromMap() {

    // TODO: check with map settings

    ui->backgroundColorRadioButton->setChecked(true);
    ui->backgroundImageRadioButton->setChecked(false);
    ui->backgroundImagePlainRadioButton->setChecked(true);
    ui->backgroundImageScaledRadioButton->setChecked(false);
    ui->backgroundImageTiledRadioButton->setChecked(false);
    // ui->backgroundImageContentWidget->setPixmap()
//    backgroundColor = QColor(map->backgroundLayer()->attributes()["color"]);
}


void MapPropertiesDialog::setDimensionUiFromMap() {

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

    ui->widthSpinBox->setValue(map->isValid() ? map->getSize().width() : 0);
    ui->heightSpinBox->setValue(map->isValid() ? map->getSize().height() : 0);
    ui->coordinatesOriginWidget->setOrigin(map->isValid() ? map->getCoordinateSystem().getOrigin()
                                                          : CoordinatesOrigin::bottomLeft);
}



void MapPropertiesDialog::setMap(AtlasPointer & atlas, MapPointer & map) {

    this->atlas = atlas;
    this->map = map;

    ui->nameEdit->setText(map->getName());
    setDimensionUiFromMap();
    setAxisUiFromMap();
    setBackgroundUiFromMap();

    ui->propertiesTabWidget->setCurrentWidget(ui->dimensionsWidget);
    ui->nameEdit->selectAll();
    ui->nameEdit->setFocus();

    // TODO: evaluate?
    //evaluate();
}


void MapPropertiesDialog::showSampleXAxis() {

    QSharedPointer<rpgmapper::model::NumeralConverter> converter;
    if (ui->xAlphaBigRadioButton->isChecked()) {
        converter = numeralConverters.alphabeticalBigCaps;
    }
    if (ui->xAlphaSmallRadioButton->isChecked()) {
        converter = numeralConverters.alphabeticalSmallCaps;
    }
    if (ui->xNumericalRadioButton->isChecked()) {
        converter = numeralConverters.numerical;
    }
    if (ui->xRomanRadioButton->isChecked()) {
        converter = numeralConverters.roman;
    }

    if (converter.data() == nullptr) {
        throw std::runtime_error("Cannot deduce unit converter for current option on X axis.");
    }

    QStringList examples;
    for (int i = 0; i < 7; ++i) {
        examples << converter->convert(i + ui->xStartValueSpinBox->value());
    }
    ui->xAxisSampleLineEdit->setText(examples.join(",") + ", ...");
    ui->xAxisSampleLineEdit->setCursorPosition(0);
}


void MapPropertiesDialog::showSampleYAxis() {

    QSharedPointer<rpgmapper::model::NumeralConverter> converter;
    if (ui->yAlphaBigRadioButton->isChecked()) {
        converter = numeralConverters.alphabeticalBigCaps;
    }
    if (ui->yAlphaSmallRadioButton->isChecked()) {
        converter = numeralConverters.alphabeticalSmallCaps;
    }
    if (ui->yNumericalRadioButton->isChecked()) {
        converter = numeralConverters.numerical;
    }
    if (ui->yRomanRadioButton->isChecked()) {
        converter = numeralConverters.roman;
    }

    if (converter.data() == nullptr) {
        throw std::runtime_error("Cannot deduce unit converter for current option on Y axis.");
    }

    QStringList examples;
    for (int i = 0; i < 7; ++i) {
        examples << converter->convert(i + ui->yStartValueSpinBox->value());
    }
    ui->yAxisSampleLineEdit->setText(examples.join(",") + ", ...");
    ui->yAxisSampleLineEdit->setCursorPosition(0);
}


void MapPropertiesDialog::widthChanged(int value) {
    if (ui->linkWidthHeightToolButton->isChecked() && (ui->heightSpinBox->value() != value)) {
        ui->heightSpinBox->setValue(value);
    }
}


void MapPropertiesDialog::initNumeralConverters() {

    if (numeralConverters.alphabeticalBigCaps.data() == nullptr) {
        numeralConverters.alphabeticalBigCaps = NumeralConverter::create("AlphaBig");
    }

    if (numeralConverters.alphabeticalSmallCaps.data() == nullptr) {
        numeralConverters.alphabeticalSmallCaps = NumeralConverter::create("AlphaSmall");
    }

    if (numeralConverters.numerical.data() == nullptr) {
        numeralConverters.numerical = NumeralConverter::create("Numeric");
    }

    if (numeralConverters.roman.data() == nullptr) {
        numeralConverters.roman = NumeralConverter::create("Roman");
    }
}

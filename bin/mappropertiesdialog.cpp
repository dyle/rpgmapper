/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QToolButton>

#include <rpgmapper/command/composite_command.hpp>
#include <rpgmapper/command/processor.hpp>
#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/command/set_map_axis_font.hpp>
#include <rpgmapper/command/set_map_axis_font_color.hpp>
#include <rpgmapper/command/set_map_background_color.hpp>
#include <rpgmapper/command/set_map_background_image.hpp>
#include <rpgmapper/command/set_map_background_image_render_mode.hpp>
#include <rpgmapper/command/set_map_background_rendering.hpp>
#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/command/set_map_margin.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/command/set_map_numeral_offset.hpp>
#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/resource_type.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/session.hpp>

#include "mappropertiesdialog.hpp"
#include "ui_mappropertiesdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;
using namespace rpgmapper::model::layer;
using namespace rpgmapper::model::resource;
using namespace rpgmapper::view;


MapPropertiesDialog::MapPropertiesDialog(QWidget * parent) : QDialog{parent} {

    ui = std::make_shared<Ui_mapPropertiesDialog>();
    ui->setupUi(this);

    initNumeralConverters();

    backgroundPreviewLabel = new BackgroundImageLabel{this};
    backgroundPreviewLabel->setMinimumSize(QSize{48,48});
    backgroundPreviewLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    backgroundPreviewLabel->setScaledContents(false);
    ui->backgroundImageScrollArea->setWidget(backgroundPreviewLabel);

    connect(ui->widthSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::widthChanged);
    connect(ui->heightSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapPropertiesDialog::heightChanged);
    connect(ui->marginSlider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            this, &MapPropertiesDialog::marginSliderValueChange);

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
    connect(ui->gridColorToolButton, &QToolButton::clicked, this, &MapPropertiesDialog::selectGridColor);

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
    connect(ui->backgroundImageFileComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this, &MapPropertiesDialog::backgroundImageSelected);

    connect(ui->okButton, &QPushButton::clicked, this, &MapPropertiesDialog::clickedOk);

    xAxisNumeralButtons = std::list<QRadioButton *>{ui->xNumericalRadioButton,
                                                    ui->xAlphaSmallRadioButton,
                                                    ui->xAlphaBigRadioButton,
                                                    ui->xRomanRadioButton};

    yAxisNumeralButtons = std::list<QRadioButton *>{ui->yNumericalRadioButton,
                                                    ui->yAlphaSmallRadioButton,
                                                    ui->yAlphaBigRadioButton,
                                                    ui->yRomanRadioButton};

    collectBackgroundImages();
}


void MapPropertiesDialog::applyAxisValuesToMap(CompositeCommand * & commands, QString newMapName) {

    if (!commands) {
        throw std::invalid_argument{"Commands argument must not be nullptr."};
    }
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }
    auto coordinateSystem = map->getCoordinateSystem();

    auto xNumeric = getSelectedXAxisNumeral();
    if (!xNumeric.isEmpty() && (xNumeric != coordinateSystem->getNumeralXAxis()->getName())) {
        commands->addCommand(CommandPointer{new SetMapNumeralAxis{newMapName, true, xNumeric}});
    }

    auto yNumeric = getSelectedYAxisNumeral();
    if (!yNumeric.isEmpty() && (yNumeric != coordinateSystem->getNumeralYAxis()->getName())) {
        commands->addCommand(CommandPointer{new SetMapNumeralAxis{newMapName, false, yNumeric}});
    }

    auto offset = QPoint{ui->xStartValueSpinBox->value(), ui->yStartValueSpinBox->value()};
    if (offset != coordinateSystem->getOffset()) {
        commands->addCommand(CommandPointer{new SetMapNumeralOffset{newMapName, offset}});
    }

    auto layers = map->getLayers();
    auto axisPalette = ui->axisColorFrame->palette();
    auto axisColor = axisPalette.window().color();
    if (layers.getAxisLayer()->getColor() != axisColor) {
        commands->addCommand(CommandPointer{new SetMapAxisFontColor{newMapName, axisColor}});
    }

    QFont axisFont;
    axisFont.fromString(ui->axisFontLineEdit->text());
    if (layers.getAxisLayer()->getFont().toString() != axisFont.toString()) {
        commands->addCommand(CommandPointer{new SetMapAxisFont{newMapName, axisFont}});
    }

    auto gridPalette = ui->gridColorFrame->palette();
    auto gridColor = gridPalette.window().color();
    if (layers.getGridLayer()->getColor() != gridColor) {
        commands->addCommand(CommandPointer{new SetMapGridColor{newMapName, gridColor}});
    }
}


void MapPropertiesDialog::applyBackgroundValuesToMap(CompositeCommand * & commands, QString newMapName) {
    
    if (!commands) {
        throw std::invalid_argument{"Commands argument must not be nullptr."};
    }
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }
    
    auto layers = map->getLayers();
    auto backgroundLayer = layers.getBackgroundLayer();
    
    auto backgroundPalette = ui->backgroundColorFrame->palette();
    auto backgroundColor = backgroundPalette.window().color();
    
    if (backgroundLayer->getColor() != backgroundColor) {
        commands->addCommand(CommandPointer{new SetMapBackgroundColor{newMapName, backgroundColor}});
    }

    if (ui->backgroundColorRadioButton->isChecked() && !backgroundLayer->isColorRendered()) {
        commands->addCommand(CommandPointer{new SetMapBackgroundRendering{newMapName, "color"}});
    }

    if (ui->backgroundImageRadioButton->isChecked() && !backgroundLayer->isImageRendered()) {
        commands->addCommand(CommandPointer{new SetMapBackgroundRendering{newMapName, "image"}});
    }

    auto selectedImage = ui->backgroundImageFileComboBox->currentText();
    if (selectedImage != tr("<applied on map>") && ui->backgroundImageRadioButton->isChecked()) {
        commands->addCommand(CommandPointer{new SetMapBackgroundImage{newMapName, selectedImage}});
    }

    auto mode = getSelectedImageRenderMode();
    if (backgroundLayer->getImageRenderMode() != mode) {
        commands->addCommand(CommandPointer{new SetMapBackgroundImageRenderMode{newMapName, mode}});
    }
}


void MapPropertiesDialog::applyDimensionValuesToMap(CompositeCommand * & commands, QString newMapName) {
    
    if (!commands) {
        throw std::invalid_argument{"Commands argument must not be nullptr."};
    }
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }
    
    auto coordinateSystem = map->getCoordinateSystem();
    
    auto newWidth = ui->widthSpinBox->value();
    auto newHeight = ui->heightSpinBox->value();
    auto mapSize = coordinateSystem->getSize();
    if ((mapSize.width() != newWidth) || (mapSize.height() != newHeight)) {
        commands->addCommand(CommandPointer{new ResizeMap{newMapName, QSize{newWidth, newHeight}}});
    }

    auto origin = ui->coordinatesOriginWidget->getOrigin();
    if (origin != coordinateSystem->getOrigin()) {
        commands->addCommand(CommandPointer{new SetMapOrigin{newMapName, origin}});
    }
    
    auto margin = getSelectedMargin();
    if (margin != coordinateSystem->getMargin()) {
        commands->addCommand(CommandPointer{new SetMapMargin{newMapName, margin}});
    }
}


void MapPropertiesDialog::applyValuesToMap() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }

    auto newMapName = map->getName();
    auto commands = new CompositeCommand{};
    if (ui->nameEdit->text() != map->getName()) {
        commands->addCommand(CommandPointer{new SetMapName(map->getName(), ui->nameEdit->text())});
        newMapName = ui->nameEdit->text();
    }

    applyDimensionValuesToMap(commands, newMapName);
    applyAxisValuesToMap(commands, newMapName);
    applyBackgroundValuesToMap(commands, newMapName);

    if (commands->size() > 0) {
        auto session = Session::getCurrentSession();
        auto processor = session->getCommandProcessor();
        processor->execute(CommandPointer{commands});
        
        if (mapName != newMapName) {
            mapName = newMapName;
            session->selectMap(newMapName);
        }
    }
    else {
        delete commands;
    }
}


void MapPropertiesDialog::backgroundImageSelected(QString backgroundImage) {

    if (backgroundImage.isEmpty()) {
        backgroundPreviewLabel->setPixmap(QPixmap{});
        backgroundPreviewLabel->update();
    }
    else {
        
        auto resource = ResourceDB::getResource(backgroundImage);
        if (!resource) {
            auto errorText = "Unknown resource: " + backgroundImage.toStdString();
            throw std::runtime_error{errorText};
        }
        
        QPixmap pixmap;
        pixmap.convertFromImage(QImage::fromData(resource->getData()));
        backgroundPreviewLabel->setPixmap(pixmap);
        backgroundPreviewLabel->update();
    }
}


void MapPropertiesDialog::clickedOk() {
    if (isUserInputValid()) {
        applyValuesToMap();
        accept();
    }
}


void MapPropertiesDialog::collectBackgroundImages() {
    
    auto backgroundResourcePrefix = getResourcePrefixForType(ResourceType::background);
    auto backgroundImageNames = ResourceDB::getResources(backgroundResourcePrefix);
    
    for (auto const & resourceName : backgroundImageNames) {
    
        auto resource = ResourceDB::getResource(resourceName);
        if (resource) {
            ui->backgroundImageFileComboBox->addItem(resourceName);
        }
    }
}


ImageRenderMode MapPropertiesDialog::getSelectedImageRenderMode() const {

    ImageRenderMode mode;

    if (ui->backgroundImagePlainRadioButton->isChecked()) {
        mode = ImageRenderMode::plain;
    }
    else
    if (ui->backgroundImageScaledRadioButton->isChecked()) {
        mode = ImageRenderMode::scaled;
    }
    else
    if (ui->backgroundImageTiledRadioButton->isChecked()) {
        mode = ImageRenderMode::tiled;
    }
    else {
        throw std::runtime_error("Don't know which background image render mode is selected.");
    }

    return mode;
}


float MapPropertiesDialog::getSelectedMargin() const {
    return static_cast<float>(ui->marginSlider->value()) / 10.0;
}


QString MapPropertiesDialog::getSelectedXAxisNumeral() const {

    QString res = QString::null;

    static std::map<QAbstractButton *, QString> const buttons {
            {ui->xNumericalRadioButton, "numeric"},
            {ui->xAlphaSmallRadioButton, "alphaSmall"},
            {ui->xAlphaBigRadioButton, "alphaBig"},
            {ui->xRomanRadioButton, "roman"}
    };

    QRadioButton * checkedButton = nullptr;
    for (auto const button : xAxisNumeralButtons) {
        if (button->isChecked()) {
            checkedButton = button;
            break;
        }
    }

    auto iter = buttons.find(checkedButton);
    if (iter != buttons.end()) {
        res = (*iter).second;
    }

    return res;
}


QString MapPropertiesDialog::getSelectedYAxisNumeral() const {

    QString res = QString::null;

    static std::map<QAbstractButton *, QString> const buttons {
            {ui->yNumericalRadioButton, "numeric"},
            {ui->yAlphaSmallRadioButton, "alphaSmall"},
            {ui->yAlphaBigRadioButton, "alphaBig"},
            {ui->yRomanRadioButton, "roman"}
    };

    QRadioButton * checkedButton = nullptr;
    for (auto const button : yAxisNumeralButtons) {
        if (button->isChecked()) {
            checkedButton = button;
            break;
        }
    }

    auto iter = buttons.find(checkedButton);
    if (iter != buttons.end()) {
        res = (*iter).second;
    }

    return res;
}


void MapPropertiesDialog::heightChanged(int value) {
    if (ui->linkWidthHeightToolButton->isChecked() && (ui->widthSpinBox->value() != value)) {
        ui->widthSpinBox->setValue(value);
    }
}


void MapPropertiesDialog::initNumeralConverters() {

    if (numeralConverters.alphabeticalBigCaps.data() == nullptr) {
        numeralConverters.alphabeticalBigCaps = NumeralConverter::create("alphaBig");
    }

    if (numeralConverters.alphabeticalSmallCaps.data() == nullptr) {
        numeralConverters.alphabeticalSmallCaps = NumeralConverter::create("alphaSmall");
    }

    if (numeralConverters.numerical.data() == nullptr) {
        numeralConverters.numerical = NumeralConverter::create("numeric");
    }

    if (numeralConverters.roman.data() == nullptr) {
        numeralConverters.roman = NumeralConverter::create("roman");
    }
}


bool MapPropertiesDialog::isUserInputValid() {

    static QString invalidNameMessage{tr("Map name is empty or contains invalid characters.")};
    static QString alreayExistingMessage{tr("Map name is already used by another map.")};

    if (!MapNameValidator::isValid(ui->nameEdit->text())) {
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
        QMessageBox::critical(this, tr("Refused to change name of map"), invalidNameMessage);
        return false;
    }
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }

    auto otherMap = Session::getCurrentSession()->findMap(ui->nameEdit->text());
    if (otherMap->isValid() && (otherMap.data() != map.data())) {
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
        QMessageBox::critical(this, tr("Refused to change name of map"), alreayExistingMessage);
        return false;
    }

    return true;
}


void MapPropertiesDialog::marginSliderValueChange(int value) {
    float margin = static_cast<float>(value) / 10.0f;
    ui->marginValue->setText(QString::number(margin, 'f', 1));
}


void MapPropertiesDialog::selectAxisColor() {

    auto axisPalette = ui->axisColorFrame->palette();
    QColor axisColor = axisPalette.window().color();
    QColor color = QColorDialog::getColor(axisColor, this);
    if (color.isValid()) {
        axisPalette.setColor(QPalette::Window, color);
        ui->axisColorFrame->setPalette(axisPalette);
    }
}


void MapPropertiesDialog::selectAxisFont() {

    QFont axisFont;
    axisFont.fromString(ui->axisFontLineEdit->text());
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, axisFont, this);
    if (ok) {
        ui->axisFontLineEdit->setText(newFont.toString());
    }
}


void MapPropertiesDialog::selectBackgroundColor() {

    auto backgroundPalette = ui->backgroundColorFrame->palette();
    QColor backgroundColor = backgroundPalette.window().color();
    QColor color = QColorDialog::getColor(backgroundColor, this);
    if (color.isValid()) {
        backgroundPalette.setColor(QPalette::Window, color);
        ui->backgroundColorFrame->setPalette(backgroundPalette);
    }
}


void MapPropertiesDialog::selectBackgroundImage() {

    auto fileName = QFileDialog::getOpenFileName(this, tr("Pick an image as map background"));
    if (fileName.isEmpty()) {
        return;
    }
    
    QFile file{fileName};
    if (file.open(QIODevice::ReadOnly)) {
        
        auto byteArray = file.readAll();
        file.close();
        ResourceDB::getLocalResources()->addResource(fileName, byteArray);
        
        ui->backgroundImageFileComboBox->addItem(fileName);
        ui->backgroundImageFileComboBox->setCurrentText(fileName);
    }
}


void MapPropertiesDialog::selectGridColor() {

    auto gridPalette = ui->gridColorFrame->palette();
    QColor gridColor = gridPalette.window().color();
    QColor color = QColorDialog::getColor(gridColor, this);
    if (color.isValid()) {
        gridPalette.setColor(QPalette::Window, color);
        ui->gridColorFrame->setPalette(gridPalette);
    }
}


void MapPropertiesDialog::setAxisUiFromMap() {

    setXAxisUiFromMap();
    setYAxisUiFromMap();
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }
    auto layers = map->getLayers();

    ui->axisFontLineEdit->setText(layers.getAxisLayer()->getFont().toString());
    auto axisPalette = ui->axisColorFrame->palette();
    axisPalette.setColor(QPalette::Window, layers.getAxisLayer()->getColor());
    ui->axisColorFrame->setPalette(axisPalette);

    auto gridPalette = ui->gridColorFrame->palette();
    gridPalette.setColor(QPalette::Window, layers.getGridLayer()->getColor());
    ui->gridColorFrame->setPalette(gridPalette);

    showSampleXAxis();
    showSampleYAxis();
}


void MapPropertiesDialog::setBackgroundImageRenderMode() {

    if (ui->backgroundImagePlainRadioButton->isChecked()) {
        backgroundPreviewLabel->setImageRenderMode(ImageRenderMode::plain);
    }
    else
    if (ui->backgroundImageScaledRadioButton->isChecked()) {
        backgroundPreviewLabel->setImageRenderMode(ImageRenderMode::scaled);
    }
    else
    if (ui->backgroundImageTiledRadioButton->isChecked()) {
        backgroundPreviewLabel->setImageRenderMode(ImageRenderMode::tiled);
    }
    
    backgroundPreviewLabel->update();
}


void MapPropertiesDialog::setBackgroundUiFromMap() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }
    auto layers = map->getLayers();
    auto backgroundLayer = layers.getBackgroundLayer();

    auto backgroundImageResource = backgroundLayer->getImageResource();
    ui->backgroundImageFileComboBox->setCurrentText(backgroundImageResource);
    
    bool coloredBackground = backgroundLayer->isColorRendered();
    bool imageBackground = backgroundLayer->isImageRendered();
    if (coloredBackground && imageBackground) {
        throw std::runtime_error("Color and image background both set on map. These are mutual exclusive.");
    }

    ui->backgroundColorRadioButton->setChecked(coloredBackground);
    ui->backgroundImageRadioButton->setChecked(imageBackground);

    ui->backgroundImagePlainRadioButton->setChecked(backgroundLayer->isImageRenderedPlain());
    ui->backgroundImageScaledRadioButton->setChecked(backgroundLayer->isImageRenderedScaled());
    ui->backgroundImageTiledRadioButton->setChecked(backgroundLayer->isImageRenderedTiled());

    auto backgroundFramePalette = ui->backgroundColorFrame->palette();
    backgroundFramePalette.setColor(QPalette::Window, backgroundLayer->getColor());
    ui->backgroundColorFrame->setPalette(backgroundFramePalette);

    setBackgroundImageRenderMode();
    setMargins();
}


void MapPropertiesDialog::setDimensionUiFromMap() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Internal map lost when applying values of property dialog.");
    }
    auto coordinateSystem = map->getCoordinateSystem();

    ui->widthSpinBox->setValue(map->isValid() ? coordinateSystem->getSize().width() : 0);
    ui->heightSpinBox->setValue(map->isValid() ? coordinateSystem->getSize().height() : 0);
    ui->coordinatesOriginWidget->setOrigin(map->isValid() ? coordinateSystem->getOrigin()
                                                          : CoordinatesOrigin::bottomLeft);
    ui->marginSlider->setValue(static_cast<int>(coordinateSystem->getMargin() * 10.0));
    marginSliderValueChange(ui->marginSlider->value());
}


void MapPropertiesDialog::setMap(QString mapName) {

    this->mapName = mapName;
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to set.");
    }

    setWindowTitle(tr("Change properties of map '%1'").arg(map->getName()));

    ui->nameEdit->setText(map->getName());
    setDimensionUiFromMap();
    setAxisUiFromMap();
    setBackgroundUiFromMap();

    ui->propertiesTabWidget->setCurrentWidget(ui->dimensionsWidget);
    ui->nameEdit->selectAll();
    ui->nameEdit->setFocus();
}


void MapPropertiesDialog::setMargins() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to set.");
    }
    
    auto margin = map->getCoordinateSystem()->getMargin();
    ui->marginSlider->setValue(static_cast<int>(margin) *10);
}


void MapPropertiesDialog::setXAxisUiFromMap() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to set.");
    }
    auto coordinateSystem = map->getCoordinateSystem();

    for (auto radioButton : xAxisNumeralButtons) {
        radioButton->setChecked(false);
    }

    using RadioButtonMap = std::map<QString, QRadioButton *>;
    static RadioButtonMap const xAxisNumericalRadioButtons = {
        {"numeric", ui->xNumericalRadioButton},
        {"alphaSmall", ui->xAlphaSmallRadioButton},
        {"alphaBig", ui->xAlphaBigRadioButton},
        {"roman", ui->xRomanRadioButton}
    };

    auto xAxisIter = xAxisNumericalRadioButtons.find(coordinateSystem->getNumeralXAxis()->getName());
    if (xAxisIter == xAxisNumericalRadioButtons.end()) {
        throw std::runtime_error("Unknown setting for map x axis numeric.");
    }

    (*xAxisIter).second->setChecked(true);
}


void MapPropertiesDialog::setYAxisUiFromMap() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw std::runtime_error("Invalid map to set.");
    }
    auto coordinateSystem = map->getCoordinateSystem();

    for (auto radioButton : yAxisNumeralButtons) {
        radioButton->setChecked(false);
    }

    using RadioButtonMap = std::map<QString, QRadioButton *>;
    static RadioButtonMap const yAxisNumericalRadioButtons = {
        {"numeric", ui->yNumericalRadioButton},
        {"alphaSmall", ui->yAlphaSmallRadioButton},
        {"alphaBig", ui->yAlphaBigRadioButton},
        {"roman", ui->yRomanRadioButton}
    };

    auto yAxisIter = yAxisNumericalRadioButtons.find(coordinateSystem->getNumeralYAxis()->getName());
    if (yAxisIter == yAxisNumericalRadioButtons.end()) {
        throw std::runtime_error("Unknown setting for map y axis numeric.");
    }

    (*yAxisIter).second->setChecked(true);
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

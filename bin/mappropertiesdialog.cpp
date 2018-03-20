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
#include <rpgmapper/filesystem.hpp>
#include <rpgmapper/command/composite_command.hpp>
#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/command/set_map_axis_font.hpp>
#include <rpgmapper/command/set_map_axis_font_color.hpp>
#include <rpgmapper/command/set_map_background_color.hpp>
#include <rpgmapper/command/set_map_background_image.hpp>
#include <rpgmapper/command/set_map_background_image_render_mode.hpp>
#include <rpgmapper/command/set_map_background_rendering.hpp>
#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/command/set_map_margins.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/command/set_map_numeral_offset.hpp>
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

    backgroundPreviewLabel = new BackgroundImageLabel{this};
    backgroundPreviewLabel->setMinimumSize(QSize{48,48});
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

}


void MapPropertiesDialog::addBackgroundImageFromFile(QFileInfo const & fileInfo) {

    if (!fileInfo.exists()) {
        return;
    }

    QImage image(fileInfo.absoluteFilePath());
    if (!image.isNull()) {
        backgroundImages[fileInfo.absoluteFilePath()] = image;
        ui->backgroundImageFileComboBox->addItem(fileInfo.absoluteFilePath());
    }
}


void MapPropertiesDialog::applyAxisValuesToMap(CompositeCommand * & commands) {

    auto atlas = this->atlas.toStrongRef();
    if (atlas == nullptr) {
        throw std::runtime_error("Atlas instance in properties vanished (nullptr).");
    }

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Internal map lost when applying values of property dialog (map == nullptr).");
    }

    auto xNumeric = getSelectedXAxisNumeral();
    if (!xNumeric.isEmpty() && (xNumeric != map->getNumeralXAxis()->getName())) {
        commands->addCommand(CommandPointer{new SetMapNumeralAxis{atlas, map->getName(), true, xNumeric}});
    }

    auto yNumeric = getSelectedYAxisNumeral();
    if (!yNumeric.isEmpty() && (yNumeric != map->getNumeralYAxis()->getName())) {
        commands->addCommand(CommandPointer{new SetMapNumeralAxis{atlas, map->getName(), false, yNumeric}});
    }

    auto offset = QPoint{ui->xStartValueSpinBox->value(), ui->yStartValueSpinBox->value()};
    if (offset != map->getCoordinateSystem().getOffset()) {
        commands->addCommand(CommandPointer{new SetMapNumeralOffset{atlas, map->getName(), offset}});
    }

    auto axisPalette = ui->axisColorFrame->palette();
    auto axisColor = axisPalette.window().color();
    if (map->getAxisLayer()->getColor() != axisColor) {
        commands->addCommand(CommandPointer{new SetMapAxisFontColor{atlas, map->getName(), axisColor}});
    }

    QFont axisFont;
    axisFont.fromString(ui->axisFontLineEdit->text());
    if (map->getAxisLayer()->getFont().toString() != axisFont.toString()) {
        commands->addCommand(CommandPointer{new SetMapAxisFont{atlas, map->getName(), axisFont}});
    }

    auto gridPalette = ui->gridColorFrame->palette();
    auto gridColor = gridPalette.window().color();
    if (map->getGridLayer()->getColor() != gridColor) {
        commands->addCommand(CommandPointer{new SetMapGridColor{atlas, map->getName(), gridColor}});
    }
}


void MapPropertiesDialog::applyBackgroundValuesToMap(CompositeCommand * & commands) {

    auto atlas = this->atlas.toStrongRef();
    if (atlas == nullptr) {
        throw std::runtime_error("Atlas instance in properties vanished (nullptr).");
    }

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Internal map lost when applying values of property dialog (map == nullptr).");
    }

    auto backgroundPalette = ui->backgroundColorFrame->palette();
    auto backgroundColor = backgroundPalette.window().color();
    if (map->getBackgroundLayer()->getColor() != backgroundColor) {
        commands->addCommand(CommandPointer{new SetMapBackgroundColor{atlas, map->getName(), backgroundColor}});
    }

    if (ui->backgroundColorRadioButton->isChecked() && !map->getBackgroundLayer()->isColorRendered()) {
        commands->addCommand(CommandPointer{new SetMapBackgroundRendering{atlas, map->getName(), "color"}});
    }

    if (ui->backgroundImageRadioButton->isChecked() && !map->getBackgroundLayer()->isImageRendered()) {
        commands->addCommand(CommandPointer{new SetMapBackgroundRendering{atlas, map->getName(), "image"}});
    }

    auto selectedImage = ui->backgroundImageFileComboBox->currentText();
    if (selectedImage != tr("<applied on map>")) {
        auto image = backgroundImages[selectedImage];
        commands->addCommand(CommandPointer{new SetMapBackgroundImage{atlas, map->getName(), image}});
    }

    auto mode = getSelectedImageRenderMode();
    if (map->getBackgroundLayer()->getImageRenderMode() != mode) {
        commands->addCommand(CommandPointer{new SetMapBackgroundImageRenderMode{atlas, map->getName(), mode}});
    }

    auto margins = getSelectedMargins();
    if (margins != map->getBackgroundLayer()->getMargins()) {
        commands->addCommand(CommandPointer{new SetMapMargins{atlas, map->getName(), margins}});
    }
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
        commands->addCommand(CommandPointer{new SetMapName(atlas, map->getName(), ui->nameEdit->text())});
    }

    applyDimensionValuesToMap(commands);
    applyAxisValuesToMap(commands);
    applyBackgroundValuesToMap(commands);

    if (commands->size() > 0) {
        atlas->getCommandProzessor()->execute(CommandPointer{commands});
    }
    else {
        delete commands;
    }
}


void MapPropertiesDialog::backgroundImageSelected(QString const & backgroundImage) {

    if (backgroundImage.isEmpty()) {
        backgroundPreviewLabel->setPixmap(QPixmap{});
        backgroundPreviewLabel->update();
    }
    else {

        if (backgroundImage == tr("<applied on map>")) {

            auto map = this->map.toStrongRef();
            if (map == nullptr) {
                throw std::runtime_error("Map instance in properties vanished (nullptr).");
            }

            QPixmap pixmap;
            pixmap.convertFromImage(map->getBackgroundLayer()->getImage());
            backgroundPreviewLabel->setPixmap(pixmap);
            backgroundPreviewLabel->update();
        }
        else {

            auto pair = backgroundImages.find(backgroundImage);
            if (pair == backgroundImages.end()) {
                throw std::runtime_error("Unable to locate image selected background image.");
            }

            QPixmap pixmap;
            pixmap.convertFromImage((*pair).second);
            backgroundPreviewLabel->setPixmap(pixmap);
            backgroundPreviewLabel->update();
        }
    }
}


void MapPropertiesDialog::clickedOk() {
    if (isUserInputValid()) {
        applyValuesToMap();
        accept();
    }
}


void MapPropertiesDialog::collectBackgroundImages() {
    backgroundImages.clear();
    collectBackgroundImagesFromUser();
    collectBackgroundImagesFromSystem();
}


void MapPropertiesDialog::collectBackgroundImagesFromSystem() {
    auto systemDataPath = rpgmapper::model::getApplicationDataSystemPath();
    if (systemDataPath.cd("backgrounds")) {
        collectBackgroundImagesInPath(systemDataPath);
    }
}


void MapPropertiesDialog::collectBackgroundImagesFromUser() {
    auto userDataPath = rpgmapper::model::getApplicationDataUserPath();
    if (userDataPath.cd("backgrounds")) {
        collectBackgroundImagesInPath(userDataPath);
    }
}


void MapPropertiesDialog::collectBackgroundImagesInPath(QDir const & path) {

    if (!path.exists()) {
        return;
    }

    QStringList imageExtension;
    imageExtension << "*.png" << "*.jpg";
    auto filter = QDir::Files | QDir::Readable | QDir::NoDotAndDotDot;
    for (auto const & fileInfo : path.entryInfoList(imageExtension, filter)) {
        addBackgroundImageFromFile(fileInfo);
    }
}


rpgmapper::model::ImageRenderMode MapPropertiesDialog::getSelectedImageRenderMode() const {

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


QMargins MapPropertiesDialog::getSelectedMargins() const {
    return QMargins(ui->leftMarginSpinBox->value(),
                    ui->topMarginSpinBox->value(),
                    ui->rightMarginSpinBox->value(),
                    ui->bottomMarginSpinBox->value());
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

    static QString invalidNameMessage{
        tr("Map name is empty or contains invalid characters (any of \"%1\").").arg(Map::getInvalidCharactersInName())};

    if (!Map::isNameValid(ui->nameEdit->text())) {
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
        QMessageBox::critical(this, tr("Refused to change name of map"), invalidNameMessage);
        return false;
    }

    auto atlas = this->atlas.toStrongRef();
    if (atlas == nullptr) {
        throw std::runtime_error("Atlas instance in properties vanished (nullptr).");
    }

    static QString alreayExistingMessage{tr("Map name is already used by another map.")};
    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }
    auto otherMap = atlas->findMap(ui->nameEdit->text());
    if (otherMap->isValid() && (otherMap.data() != map.data())) {
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
        QMessageBox::critical(this, tr("Refused to change name of map"), alreayExistingMessage);
        return false;
    }

    return true;
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

    auto filename = QFileDialog::getOpenFileName(this, tr("Pick an image as map background"));
    if (filename.isEmpty()) {
        return;
    }

    QImage backgroundImage{filename};
    if (backgroundImage.isNull()) {
        QString message = QString{tr("Failed to load image '%1'\nIs this an image?")}.arg(filename);
        QMessageBox::critical(this, tr("Failed to load image."), message);
        return;
    }

    backgroundImages[filename] = backgroundImage;
    ui->backgroundImageFileComboBox->addItem(filename);
    ui->backgroundImageFileComboBox->setCurrentText(filename);
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

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

    ui->axisFontLineEdit->setText(map->getAxisLayer()->getFont().toString());
    auto axisPalette = ui->axisColorFrame->palette();
    axisPalette.setColor(QPalette::Window, map->getAxisLayer()->getColor());
    ui->axisColorFrame->setPalette(axisPalette);

    auto gridPalette = ui->gridColorFrame->palette();
    gridPalette.setColor(QPalette::Window, map->getGridLayer()->getColor());
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

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

    ui->backgroundImageFileComboBox->clear();
    auto backgroundImage = map->getBackgroundLayer()->getImage();
    if (!backgroundImage.isNull()) {
        QPixmap pixmap;
        pixmap.convertFromImage(backgroundImage);
        backgroundPreviewLabel->setPixmap(pixmap);
        ui->backgroundImageFileComboBox->addItem(tr("<applied on map>"));
        ui->backgroundImageFileComboBox->setCurrentIndex(0);
    }
    collectBackgroundImages();

    bool coloredBackground = map->getBackgroundLayer()->isColorRendered();
    bool imageBackground = map->getBackgroundLayer()->isImageRendered();
    if (coloredBackground && imageBackground) {
        throw std::runtime_error("Color and image background both set on map. These are mutual exclusive.");
    }

    ui->backgroundColorRadioButton->setChecked(coloredBackground);
    ui->backgroundImageRadioButton->setChecked(imageBackground);

    ui->backgroundImagePlainRadioButton->setChecked(map->getBackgroundLayer()->isImageRenderedPlain());
    ui->backgroundImageScaledRadioButton->setChecked(map->getBackgroundLayer()->isImageRenderedScaled());
    ui->backgroundImageTiledRadioButton->setChecked(map->getBackgroundLayer()->isImageRenderedTiled());

    auto backgroundFramePalette = ui->backgroundColorFrame->palette();
    backgroundFramePalette.setColor(QPalette::Window, map->getBackgroundLayer()->getColor());
    ui->backgroundColorFrame->setPalette(backgroundFramePalette);

    setBackgroundImageRenderMode();
    setMargins();
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

    Map * oldMap = this->map.data();

    this->atlas = atlas;
    this->map = map;

    setWindowTitle(tr("Change properties of map '%1'").arg(map->getName()));

    ui->nameEdit->setText(map->getName());
    setDimensionUiFromMap();
    setAxisUiFromMap();
    setBackgroundUiFromMap();

    if (oldMap != this->map.data()) {
        ui->propertiesTabWidget->setCurrentWidget(ui->dimensionsWidget);
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
    }
}


void MapPropertiesDialog::setMargins() {

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

    auto margins = map->getBackgroundLayer()->getMargins();
    ui->leftMarginSpinBox->setValue(margins.left());
    ui->topMarginSpinBox->setValue(margins.top());
    ui->rightMarginSpinBox->setValue(margins.right());
    ui->bottomMarginSpinBox->setValue(margins.bottom());
}


void MapPropertiesDialog::setXAxisUiFromMap() {

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

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

    auto xAxisIter = xAxisNumericalRadioButtons.find(map->getNumeralXAxis()->getName());
    if (xAxisIter == xAxisNumericalRadioButtons.end()) {
        throw std::runtime_error("Unknown setting for map x axis numeric.");
    }

    (*xAxisIter).second->setChecked(true);
}


void MapPropertiesDialog::setYAxisUiFromMap() {

    auto map = this->map.toStrongRef();
    if (map == nullptr) {
        throw std::runtime_error("Map instance in properties vanished (nullptr).");
    }

    for (auto radioButton : yAxisNumeralButtons) {
        radioButton->setChecked(false);
    }

    using RadioButtonMap = std::map<QString, QRadioButton *>;
    static RadioButtonMap const yAxisNumericalRadioButtons = {
        {"aumeric", ui->yNumericalRadioButton},
        {"alphaSmall", ui->yAlphaSmallRadioButton},
        {"alphaBig", ui->yAlphaBigRadioButton},
        {"roman", ui->yRomanRadioButton}
    };

    auto yAxisIter = yAxisNumericalRadioButtons.find(map->getNumeralYAxis()->getName());
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

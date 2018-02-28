/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QStatusBar>

#include <rpgmapper/atlas_io.hpp>
#include <rpgmapper/command/set_atlas_name.hpp>
#include <rpgmapper/command/set_region_name.hpp>
#include "mainwindow.hpp"
#include "visibility_action_filter.hpp"
#include "ui_mainwindow.h"

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;
using namespace rpgmapper::view;


MainWindow::MainWindow() : QMainWindow{} {

    ui = std::make_shared<Ui_mainwindow>();
    ui->setupUi(this);

    coordinatesWidget = new CoordinatesWidget{this};
    statusBar()->addPermanentWidget(coordinatesWidget);
    statusBar()->setSizeGripEnabled(false);
    statusBar()->setVisible(true);

    selection = SelectionPointer(new rpgmapper::model::Selection{this});
    selection->setAtlas(AtlasPointer{new Atlas});
    selection->getAtlas()->init();

    ui->atlasTreeWidget->setSelection(selection);
    ui->mapTabWidget->setSelection(selection);

    ui->mapTabWidget->clear();
    ui->atlasTreeWidget->selectFirstMap();
    ui->atlasTreeNewMapToolButton->setDefaultAction(ui->actionCreateNewMap);
    ui->atlasTreeNewRegionToolButton->setDefaultAction(ui->actionCreateNewRegion);
    ui->atlasTreeDeleteMapToolButton->setDefaultAction(ui->actionDeleteMap);
    ui->atlasTreeDeleteRegionToolButton->setDefaultAction(ui->actionDeleteRegion);

    setupDialogs();
    connectActions();
    connectModelSignals();
    loadSettings();
    setApplicationWindowTitle();
}


void MainWindow::addRecentFileName(QString const & fileName) {

    if (fileName.isEmpty()) {
        return;
    }

    if (!recentAtlasFileNames.contains(fileName)) {
        recentAtlasFileNames.push_front(fileName);
        while (recentAtlasFileNames.size() > maximumRecentAtlasFiles) {
            recentAtlasFileNames.removeLast();
        }
    }

    QFileInfo fileInfo(fileName);
    if (fileInfo.isFile()) {
        recentAtlasFolderName = fileInfo.absoluteDir().absolutePath();
    }

    createRecentFileActions();
}


void MainWindow::atlasNameChanges(UNUSED QString newName) {
    setApplicationWindowTitle();
}


void MainWindow::centerWindow() {

    auto desktop = dynamic_cast<QApplication *>(QApplication::instance())->desktop();
    auto width = static_cast<int>(desktop->width() * 0.8);
    auto height = static_cast<int>(desktop->height() * 0.8);
    int x = (desktop->width() - width) / 2;
    int y = (desktop->height() - height) / 2;

    resize(QSize{width, height});
    move(QPoint{x, y});
}


void MainWindow::clearListOfRecentFiles() {

    for (auto & cAction: recentFileLoadActions) {
        delete cAction;
    }
    recentFileLoadActions.clear();
    recentAtlasFileNames.clear();

    enableActions();
}


void MainWindow::clearRecentFileActions() {

    for (auto & actionInMenu : ui->openRecentMenu->actions()) {
        if (actionInMenu != ui->actionClearRecentList) {
            ui->openRecentMenu->removeAction(actionInMenu);
        }
    }
    for (auto & action : recentFileLoadActions) {
        action->deleteLater();
    }
    recentFileLoadActions.clear();
}


void MainWindow::closeEvent(QCloseEvent * event) {
    saveSettings();
    QMainWindow::closeEvent(event);
}


void MainWindow::connectActions() {


//    connect(ui->acCloseMap, &QAction::triggered, ui->tabMap, &MapTabWidget::closeCurrentMap);
//    connect(ui->acDeleteMap, &QAction::triggered, this, &MainWindow::deleteMap);
//    connect(ui->acDeleteRegion, &QAction::triggered, this, &MainWindow::deleteRegion);
//    connect(ui->acNewMap, &QAction::triggered, this, &MainWindow::createdMap);
//    connect(ui->acNewRegion, &QAction::triggered, this, &MainWindow::createdRegion);

    connect(ui->actionClearRecentList, &QAction::triggered, this, &MainWindow::clearListOfRecentFiles);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionOpenAtlasFile, &QAction::triggered, this, &MainWindow::load);
    connect(ui->actionShowAboutDialog, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionShowAtlasProperties, &QAction::triggered, this, &MainWindow::editAtlasProperties);
    connect(ui->actionShowMapProperties, &QAction::triggered, this, &MainWindow::editMapProperties);
    connect(ui->actionShowRegionProperties, &QAction::triggered, this, &MainWindow::editRegionProperties);
    connect(ui->actionSaveAtlasFile, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSaveAtlasFileAs, &QAction::triggered, this, &MainWindow::saveAs);

    connect(ui->actionViewColorPicker, &QAction::triggered, this, &MainWindow::visibleColorPicker);
    connect(ui->actionViewMinimap, &QAction::triggered, this, &MainWindow::visibleMinimap);
    connect(ui->actionViewStructureTree, &QAction::triggered, this, &MainWindow::visibleStructure);
    connect(ui->actionViewTilesDock, &QAction::triggered, this, &MainWindow::visibleTiles);
    new VisibiltyActionFiler(ui->miniMapDockWidget, ui->actionViewMinimap, this);
    new VisibiltyActionFiler(ui->atlasStructureDockWidget, ui->actionViewStructureTree, this);
    new VisibiltyActionFiler(ui->tilesDockWidget, ui->actionViewTilesDock, this);
    new VisibiltyActionFiler(ui->colorPickerDockWidget, ui->actionViewColorPicker, this);

    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedAtlas,
            ui->actionShowAtlasProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedMap,
            ui->actionShowMapProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedRegion,
            ui->actionShowRegionProperties, &QAction::trigger);

    connect(ui->mapTabWidget, &MapTabWidget::hoverCoordinates, this, &MainWindow::showCoordinates);
}


void MainWindow::connectModelSignals() {
    connect(selection->getAtlas().data(), &Atlas::nameChanged, this, &MainWindow::atlasNameChanges);
    connect(selection->getAtlas().data(), &Atlas::regionNameChanged, this, &MainWindow::setApplicationWindowTitle);
}


void MainWindow::createRecentFileActions() {

    clearRecentFileActions();

    for (auto const & fileName: recentAtlasFileNames) {

        auto loadRecentFileAction = new QAction(this);
        loadRecentFileAction->setObjectName(fileName);
        loadRecentFileAction->setText(fileName);
        connect(loadRecentFileAction, &QAction::triggered, this, &MainWindow::loadRecentFile);

        recentFileLoadActions.push_back(loadRecentFileAction);
    }

    ui->openRecentMenu->insertActions(ui->actionClearRecentList, recentFileLoadActions);
    ui->openRecentMenu->insertSeparator(ui->actionClearRecentList);

    enableActions();
}


void MainWindow::editAtlasProperties() {

    bool changed = false;
    auto atlasName = QInputDialog::getText(this,
                                           tr("Atlas Properties"),
                                           tr("New name of atlas:"),
                                           QLineEdit::Normal,
                                           selection->getAtlas()->getName(),
                                           &changed);

    if (!changed || atlasName.isEmpty()) {
        return;
    }

    auto command = CommandPointer{new SetAtlasName{selection->getAtlas(), atlasName}};
    selection->getAtlas()->getCommandProzessor()->execute(command);
}


void MainWindow::editMapProperties() {
    auto map = selection->getMap();
    if (!map->isValid()) {
        return;
    }
    mapPropertiesDialog->setMap(map);
    mapPropertiesDialog->exec();
}


void MainWindow::editRegionProperties() {

    bool changed = false;
    auto region = selection->getRegion();
    if (!region->isValid()) {
        return;
    }

    auto regionName = QInputDialog::getText(this,
                                            tr("Region Properties"),
                                            tr("New name of region:"),
                                            QLineEdit::Normal,
                                            region->getName(),
                                            &changed);

    if (!changed || regionName.isEmpty()) {
        return;
    }

    auto command = CommandPointer{new SetRegionName{selection->getAtlas(), region->getName(), regionName}};
    selection->getAtlas()->getCommandProzessor()->execute(command);
}


void MainWindow::enableActions() {
    ui->actionClearRecentList->setEnabled(!recentAtlasFileNames.empty());
}


rpgmapper::model::AtlasPointer & MainWindow::getAtlas() {
    return selection->getAtlas();
}


rpgmapper::model::AtlasPointer const & MainWindow::getAtlas() const {
    return selection->getAtlas();
}


void MainWindow::load() {

    auto nAnswer = loadAtlasDialog->exec();
    if ((nAnswer == 0) || loadAtlasDialog->selectedFiles().empty()) {
        return;
    }
    loadAtlas(loadAtlasDialog->selectedFiles().first());
}


void MainWindow::loadAtlas(QString const & fileName) {

    QFile file{fileName};
    AtlasIO atlasIO;
    auto result = atlasIO.read(file);

    if (!result.hasSuccess()) {
        logDialog->setWindowTitle(tr("Load atlas failure"));
        logDialog->clear();
        logDialog->setMessage(tr("Failed to load atlas file."));
        logDialog->setLog(result.getLog());
        logDialog->exec();
    }
    else {
        addRecentFileName(fileName);
        selection->setAtlas(result.getAtlas());
    }
}


void MainWindow::loadRecentFile() {

    auto action = dynamic_cast<QAction *>(sender());
    if (!action) {
        return;
    }

    // we could use cAction->text(). However, Qt automagically adds
    // the shortcut literal '&' to the text, disturbing the file name.
    loadAtlas(action->objectName());
}


void MainWindow::loadSettings() {

    QSettings settings{"rpgmapper", "rpgmapper"};

    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
    }
    else {
        centerWindow();
    }
    restoreState(settings.value("windowState").toByteArray());

    maximumRecentAtlasFiles = settings.value("recent/maximum", 10).toInt();
    recentAtlasFolderName = settings.value("recent/folder").toString();
    recentAtlasFileNames.clear();
    for (int i = 0; i < maximumRecentAtlasFiles; ++i) {
        QString fileName = settings.value("recent/file-" + QString::number(i), "").toString();
        if (!fileName.isEmpty()) {
            recentAtlasFileNames.append(fileName);
        }
    }
    createRecentFileActions();

    if (!recentAtlasFolderName.isEmpty()) {
        loadAtlasDialog->setDirectory(recentAtlasFolderName);
        saveAtlasDialog->setDirectory(recentAtlasFolderName);
    }
}


void MainWindow::save() {

    if (getAtlas()->getFileName().isEmpty()) {
        saveAs();
        return;
    }
    saveAtlas(getAtlas()->getFileName());
}


void MainWindow::saveAs() {

    auto answer = saveAtlasDialog->exec();
    if ((answer == 0) || saveAtlasDialog->selectedFiles().empty()) {
        return;
    }
    saveAtlas(saveAtlasDialog->selectedFiles().first());
}


void MainWindow::saveAtlas(QString const & fileName) {

    QFile file{fileName};
    AtlasIO atlasIO;
    auto result = atlasIO.write(getAtlas(), file);

    if (!result.hasSuccess()) {
        logDialog->setWindowTitle(tr("Save atlas failure"));
        logDialog->clear();
        logDialog->setMessage(tr("Failed to save atlas file."));
        logDialog->setLog(result.getLog());
        logDialog->exec();
    }
    else {
        addRecentFileName(getAtlas()->getFileName());
    }
}


void MainWindow::saveSettings() {
    QSettings settings{"rpgmapper", "rpgmapper"};
    saveSettingsWindow(settings);
    saveSettingsRecentFiles(settings);
}


void MainWindow::saveSettingsRecentFiles(QSettings & settings) {

    settings.remove("recent");
    settings.setValue("recent/maximum", maximumRecentAtlasFiles);
    settings.setValue("recent/folder", recentAtlasFolderName);

    int fileIndex = 0;
    for (auto const & fileName : recentAtlasFileNames){
        settings.setValue("recent/file-" + QString::number(++fileIndex), fileName);
        if (fileIndex >= maximumRecentAtlasFiles) {
            break;
        }
    }
}


void MainWindow::saveSettingsWindow(QSettings & settings) {
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}


void MainWindow::setApplicationWindowTitle() {
    auto atlas = selection->getAtlas();
    auto changed = atlas->getCommandProzessor()->modifications() == 0 ? "" : " * ";
    auto title = QString("%1%2 - %3").arg(atlas->getName()).arg(changed).arg(qApp->applicationName());
    setWindowTitle(title);
}


void MainWindow::setupDialogs() {

    QStringList fileNameFilters;
    fileNameFilters << tr("Atlas files [*.atlas] (*.atlas)")
                    << tr("Any files [*.*] (*)");

    aboutDialog = new AboutDialog(this);

    loadAtlasDialog = new QFileDialog(this);
    loadAtlasDialog->setFileMode(QFileDialog::ExistingFile);
    loadAtlasDialog->setNameFilters(fileNameFilters);
    loadAtlasDialog->setAcceptMode(QFileDialog::AcceptOpen);
    loadAtlasDialog->setWindowTitle(tr("Load Atlas file"));
    loadAtlasDialog->setDirectory(recentAtlasFolderName);

    logDialog = new LogDialog(this);

    mapPropertiesDialog = new MapPropertiesDialog(this);

    saveAtlasDialog = new QFileDialog(this);
    saveAtlasDialog->setFileMode(QFileDialog::AnyFile);
    saveAtlasDialog->setNameFilters(fileNameFilters);
    saveAtlasDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveAtlasDialog->setWindowTitle(tr("Save Atlas file"));
    saveAtlasDialog->setDirectory(recentAtlasFolderName);
}


void MainWindow::showAboutDialog() {
    aboutDialog->exec();
}


void MainWindow::showCoordinates(int x, int y) {

    if (selection->getMap()->isValid()) {
        coordinatesWidget->showCoordinates(selection->getMap()->getCoordinateSystem().getNumeralCoordinates(x, y));
    }
    else {
        coordinatesWidget->clear();
    }
}


void MainWindow::showEvent(QShowEvent * cEvent) {

    QMainWindow::showEvent(cEvent);

    static bool bFirstTime = true;
    if (bFirstTime) {

        // ugly hack, since I did not investigate how Qt saves
        // the visibility state in the saveState() and restoreState()
        // methods of the QDockWindow children --> anyone?
        ui->actionViewMinimap->setChecked(ui->miniMapDockWidget->isVisible());
        ui->actionViewStructureTree->setChecked(ui->atlasStructureDockWidget->isVisible());
        ui->actionViewTilesDock->setChecked(ui->tilesDockWidget->isVisible());
        bFirstTime = false;
    }
}


void MainWindow::visibleColorPicker(bool visible) {
    ui->colorPickerDockWidget->setVisible(visible);
}


void MainWindow::visibleMinimap(bool visible) {
    ui->miniMapDockWidget->setVisible(visible);
}


void MainWindow::visibleStructure(bool visible) {
    ui->atlasStructureDockWidget->setVisible(visible);
}


void MainWindow::visibleTiles(bool visible) {
    ui->tilesDockWidget->setVisible(visible);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QStatusBar>

#include <rpgmapper/atlas_io.hpp>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


MainWindow::MainWindow() : QMainWindow{} {

    ui = std::make_shared<Ui_mainwindow>();
    ui->setupUi(this);

    coordinatesWidget = new CoordinatesWidget{this};
    statusBar()->addPermanentWidget(coordinatesWidget);
    statusBar()->setSizeGripEnabled(false);
    statusBar()->setVisible(true);

    selection = new Selection{this};
    selection->setAtlas(AtlasPointer{new Atlas});

    ui->atlasTreeWidget->setSelection(selection);

    ui->mapTabWidget->clear();
    ui->atlasTreeWidget->selectFirstMap();
    ui->atlasTreeNewMapToolButton->setDefaultAction(ui->actionCreateNewMap);
    ui->atlasTreeNewRegionToolButton->setDefaultAction(ui->actionCreateNewRegion);
    ui->atlasTreeDeleteMapToolButton->setDefaultAction(ui->actionDeleteMap);
    ui->atlasTreeDeleteRegionToolButton->setDefaultAction(ui->actionDeleteRegion);

    setupDialogs();
    connectActions();
    loadSettings();
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


void MainWindow::centerWindow() {

    const int defaultWidth = 600;
    const int defaultHeight = 400;

    auto desktop = dynamic_cast<QApplication *>(QApplication::instance())->desktop();
    int x = (desktop->width() - defaultWidth) / 2;
    int y = (desktop->height() - defaultHeight) / 2;

    resize(QSize{defaultWidth, defaultHeight});
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

    connect(ui->actionShowAboutDialog, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionOpenAtlasFile, &QAction::triggered, this, &MainWindow::load);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);

//    connect(ui->acAtlasProperties, &QAction::triggered, this, &MainWindow::editAtlasProperties);
//    connect(ui->acCloseMap, &QAction::triggered, ui->tabMap, &MapTabWidget::closeCurrentMap);
//    connect(ui->acDeleteMap, &QAction::triggered, this, &MainWindow::deleteMap);
//    connect(ui->acDeleteRegion, &QAction::triggered, this, &MainWindow::deleteRegion);
//    connect(ui->acMapProperties, &QAction::triggered, this, &MainWindow::editMapProperties);
//    connect(ui->acNewMap, &QAction::triggered, this, &MainWindow::newMap);
//    connect(ui->acNewRegion, &QAction::triggered, this, &MainWindow::newRegion);
    connect(ui->actionClearRecentList, &QAction::triggered, this, &MainWindow::clearListOfRecentFiles);
//    connect(ui->acRegionProperties, &QAction::triggered, this, &MainWindow::editRegionProperties);
    connect(ui->actionSaveAtlasFile, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSaveAtlasFileAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionViewMinimap, &QAction::triggered, this, &MainWindow::visibleMinimap);
    connect(ui->actionViewStructureTree, &QAction::triggered, this, &MainWindow::visibleStructure);
    connect(ui->actionViewTilesDock, &QAction::triggered, this, &MainWindow::visibleTiles);

    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedAtlas,
            ui->actionShowAtlasProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedMap,
            ui->actionShowMapProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedRegion,
            ui->actionShowRegionProperties, &QAction::trigger);

    connect(ui->mapTabWidget, &MapTabWidget::hoverCoordinates, this, &MainWindow::showCoordinates);
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


void MainWindow::setupDialogs() {

    QStringList cFileNameFilters;
    cFileNameFilters << tr("Atlas files [*.atlas] (*.atlas)")
                     << tr("Any files [*.*] (*)");

    aboutDialog = new AboutDialog(this);

    loadAtlasDialog = new QFileDialog(this);
    loadAtlasDialog->setFileMode(QFileDialog::ExistingFile);
    loadAtlasDialog->setNameFilters(cFileNameFilters);
    loadAtlasDialog->setAcceptMode(QFileDialog::AcceptOpen);
    loadAtlasDialog->setWindowTitle(tr("Load Atlas file"));
    loadAtlasDialog->setDirectory(recentAtlasFolderName);

    logDialog = new LogDialog(this);

    mapPropertiesDialog = new MapPropertiesDialog(this);

    saveAtlasDialog = new QFileDialog(this);
    saveAtlasDialog->setFileMode(QFileDialog::AnyFile);
    saveAtlasDialog->setNameFilters(cFileNameFilters);
    saveAtlasDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveAtlasDialog->setWindowTitle(tr("Save Atlas file"));
    saveAtlasDialog->setDirectory(recentAtlasFolderName);
}


void MainWindow::showAboutDialog() {
    aboutDialog->exec();
}


void MainWindow::showCoordinates(int x, int y) {

    if (selection->getMap()->isValid()) {
        // TODO
        // auto cUserCoordinates = selection->getMap()->translate(x, y);
        // coordinatesWidget->showCoordinates(cUserCoordinates.m_sX, cUserCoordinates.m_sY);
        NumeralCoordinates coordinates{QString::number(x), QString::number(y)};
        coordinatesWidget->showCoordinates(coordinates);
    }
    else {
        coordinatesWidget->clear();
    }
}


void MainWindow::showEvent(QShowEvent * cEvent) {

    QMainWindow::showEvent(cEvent);

    static bool bFirstTime = true;
    if (bFirstTime) {

        // ugly hack, since I did not get how Qt saves the visibility state
        // in the saveState() and restoreState() methods of the QDockWindow children
        // --> anyone?
        ui->actionViewMinimap->setChecked(ui->miniMapDockWidget->isVisible());
        ui->actionViewStructureTree->setChecked(ui->atlasStructureDockWidget->isVisible());
        ui->actionViewTilesDock->setChecked(ui->tilesDockWidget->isVisible());
        bFirstTime = false;
    }
}


void MainWindow::visibleMinimap(bool view) {
    ui->miniMapDockWidget->setVisible(view);
}


void MainWindow::visibleStructure(bool view) {
    ui->atlasStructureDockWidget->setVisible(view);
}


void MainWindow::visibleTiles(bool view) {
    ui->tilesDockWidget->setVisible(view);
}


// TODO DOCKWINDOW CLOSE CLICK DOES NOT SWITCH TOOLBUTTONS IN MENU
















#if 0


// ------------------------------------------------------------
// incs

// Qt
#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QStatusBar>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>
#include "view/aboutdialog.hpp"
#include "view/coordinatewidget.hpp"
#include "view/logdialog.hpp"
#include "mainwindow.hpp"
#include "view/mappropertiesdialog.hpp"
#include "view/structuraltreewidget.hpp"

#include "ui_mainwindow.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace view {


/**
 * Internal data of a MainWindow object.
 */
class MainWindow::MainWindow_data {

public:

    MainWindow_data() = default;

    std::shared_ptr<Ui_mainwindow> ui;                      /**< User interface. */

    QStringList m_cRecentAtlasFiles;                        /**< Recently loaded atlas files. */
    QString m_sRecentAtlasFolder;                           /**< Folder location of last recent atlas files. */
    int m_nMaximumRecentAtlasFiles = 10;                    /**< Number of recent files should be remembered. */
    QList<QAction *> m_cRecentFileActions;                  /**< List of recent file actions. */

    AboutDialog * m_cDlgAbout = nullptr;                    /**< About RPGMapper dialog. */
    QFileDialog * m_cDlgLoad = nullptr;                     /**< Load file dialog. */
    LogDialog * m_cDlgLog = nullptr;                        /**< Dialog for some log messages. */
    MapPropertiesDialog * m_cDlgMapProperties = nullptr;    /**< Dialog letting the user adjust the map properties. */
    QFileDialog * m_cDlgSaveAs = nullptr;                   /**< SaveAs file dialog. */

    CoordinateWidget * m_cWdCoordinates = nullptr;          /**< X,Y coordinates in the statusbar. */
};


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 */
MainWindow::MainWindow() : QMainWindow{} {

    d = std::make_shared<MainWindow::MainWindow_data>();

    d->ui = std::make_shared<Ui_mainwindow>();
    d->ui->setupUi(this);
    d->m_cWdCoordinates = new CoordinateWidget{this};
    statusBar()->addPermanentWidget(d->m_cWdCoordinates);
    statusBar()->setSizeGripEnabled(false);
    statusBar()->setVisible(true);

    setupDialogs();
    connectActions();
    loadSettings();

    // some fixes not caught by the Qt Designer
    addAction(d->ui->acCloseMap);

    d->ui->tabMap->clear();
    d->ui->twAtlas->resetStructure();
    d->ui->twAtlas->selectFirstMap();
    d->ui->tbAtlasTreeNewMap->setDefaultAction(d->ui->acNewMap);
    d->ui->tbAtlasTreeNewRegion->setDefaultAction(d->ui->acNewRegion);
    d->ui->tbAtlasTreeDeleteMap->setDefaultAction(d->ui->acDeleteMap);
    d->ui->tbAtlasTreeDeleteRegion->setDefaultAction(d->ui->acDeleteRegion);

    connect(Controller::instance().atlas().data(), &Atlas::changedAtlas, this, &MainWindow::changedAtlas);

    enableActions();
    changedAtlas();
}


/**
 * The atlas changed.
 */
void MainWindow::changedAtlas() {

    auto cAtlas = Controller::instance().atlas();
    QString sModifiedMarker = cAtlas->isModified() ? "*" : "";
    QString sTitle = cAtlas->name() + sModifiedMarker + " - RPGMapper V" + VERSION;
    setWindowTitle(sTitle);
}


/**
 * The current map should be deleted.
 */
void MainWindow::deleteMap() {

    auto cMap = Controller::instance().atlas()->currentMap();
    if (cMap.data() == nullptr) {
        return;
    }

    QString sQuestion = tr(
            "Do you really want to delete the map '%1'?\n\n"
            "This action is not reversible!").arg(cMap->name());

    if (QMessageBox::question(this, tr("Delete the current map."), sQuestion) == QMessageBox::Yes) {
        Controller::instance().atlas()->deleteMap(cMap->id());
    }
}


/**
 * The current region should be deleted.
 */
void MainWindow::deleteRegion() {

    auto cRegion = Controller::instance().atlas()->currentRegion();
    if (cRegion.data() == nullptr) {
        return;
    }

    QString sQuestion = tr(
            "Do you really want to delete the region '%1' and all related maps?\n\n"
            "This action is not reversible!").arg(cRegion->name());

    if (QMessageBox::question(this, tr("Delete the current map."), sQuestion) == QMessageBox::Yes) {
        Controller::instance().atlas()->deleteRegion(cRegion->id());
    }
}


/**
 * Let the user edit the properties of the current atlas.
 */
void MainWindow::editAtlasProperties() {

    bool bChange = false;
    auto sAtlasName = QInputDialog::getText(this,
                                            tr("Atlas Properties"),
                                            tr("New name of atlas:"),
                                            QLineEdit::Normal,
                                            Controller::instance().atlas()->name(),
                                            &bChange);

    if (!bChange || sAtlasName.isEmpty()) {
        return;
    }
    Controller::instance().atlas()->setName(sAtlasName);
}


/**
 * Let the user edit the properties of the current selected map.
 */
void MainWindow::editMapProperties() {
    d->m_cDlgMapProperties->setMap(Controller::instance().atlas()->currentMap());
    d->m_cDlgMapProperties->exec();
}


/**
 * Let the user edit the properties of the current selected region.
 */
void MainWindow::editRegionProperties() {

    bool bChange = false;
    auto cRegion = Controller::instance().atlas()->currentRegion();

    auto sRegionName = QInputDialog::getText(this,
                                             tr("Region Properties"),
                                             tr("New name of region:"),
                                             QLineEdit::Normal,
                                             cRegion->name(),
                                             &bChange);

    if (!bChange || sRegionName.isEmpty()) {
        return;
    }
    cRegion->setName(sRegionName);
}


/**
 * A new map shall be created.
 */
void MainWindow::newMap() {
    Controller::instance().instance().atlas()->createMap();
}


/**
 * A new region shall be created.
 */
void MainWindow::newRegion() {
    Controller::instance().instance().atlas()->createRegion();
}


/**
 * Reapply the atlas to teh whole view.
 */
void MainWindow::resetAtlas() {
    changedAtlas();
    d->ui->twAtlas->resetStructure();
}




#endif
/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QStatusBar>

#include "mainwindow.hpp"
#include "mainwindow_impl.hpp"

using namespace rpgmapper::view;


MainWindow::MainWindow() : QMainWindow{} {

    impl = std::make_shared<MainWindow::Impl>(this);

    statusBar()->setSizeGripEnabled(false);
    statusBar()->setVisible(true);

    setupDialogs();
    connectActions();
    loadSettings();
}


void MainWindow::centerWindow() {

    const int defaultWidth = 600;
    const int defaultHeight = 400;

    //QDesktopWidget * desktop = dynamic_cast<QApplication *>(QApplication::instance())->desktop();
    auto desktop = dynamic_cast<QApplication *>(QApplication::instance())->desktop();
    int x = (desktop->width() - defaultWidth) / 2;
    int y = (desktop->height() - defaultHeight) / 2;

    resize(QSize{defaultWidth, defaultHeight});
    move(QPoint{x, y});
}


void MainWindow::closeEvent(QCloseEvent * event) {
    saveSettings();
    QMainWindow::closeEvent(event);
}


void MainWindow::connectActions() {

    // TODO
//    connect(d->ui->acAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
//    connect(d->ui->acAtlasProperties, &QAction::triggered, this, &MainWindow::editAtlasProperties);
//    connect(d->ui->acCloseMap, &QAction::triggered, d->ui->tabMap, &MapTabWidget::closeCurrentMap);
//    connect(d->ui->acDeleteMap, &QAction::triggered, this, &MainWindow::deleteMap);
//    connect(d->ui->acDeleteRegion, &QAction::triggered, this, &MainWindow::deleteRegion);
//    connect(d->ui->acMapProperties, &QAction::triggered, this, &MainWindow::editMapProperties);
//    connect(d->ui->acNewMap, &QAction::triggered, this, &MainWindow::newMap);
//    connect(d->ui->acNewRegion, &QAction::triggered, this, &MainWindow::newRegion);
//    connect(d->ui->acOpen, &QAction::triggered, this, &MainWindow::load);
//    connect(d->ui->acQuit, &QAction::triggered, this, &MainWindow::close);
//    connect(d->ui->acRecentListClear, &QAction::triggered, this, &MainWindow::clearListOfRecentFiles);
//    connect(d->ui->acRegionProperties, &QAction::triggered, this, &MainWindow::editRegionProperties);
//    connect(d->ui->acSave, &QAction::triggered, this, &MainWindow::save);
//    connect(d->ui->acSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
//    connect(d->ui->acViewMinimap, &QAction::triggered, this, &MainWindow::visibleMinimap);
//    connect(d->ui->acViewStructure, &QAction::triggered, this, &MainWindow::visibleStructure);
//    connect(d->ui->acViewTiles, &QAction::triggered, this, &MainWindow::visibleTiles);
//
//    connect(d->ui->twAtlas, &StructuralTreeWidget::doubleClickedAtlas, d->ui->acAtlasProperties, &QAction::trigger);
//    connect(d->ui->twAtlas, &StructuralTreeWidget::doubleClickedMap, d->ui->acMapProperties, &QAction::trigger);
//    connect(d->ui->twAtlas, &StructuralTreeWidget::doubleClickedRegion, d->ui->acRegionProperties, &QAction::trigger);
//
//    connect(d->ui->tabMap, &MapTabWidget::hoverCoordinates, this, &MainWindow::showCoordinates);
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

    // TODO
    //d->m_nMaximumRecentAtlasFiles = settings.value("recent/maximum", 10).toInt();
    //d->m_sRecentAtlasFolder = settings.value("recent/folder").toString();
    //d->m_cRecentAtlasFiles.clear();
    //for (int i = 0; i < d->m_nMaximumRecentAtlasFiles; ++i) {
    //    QString sFilename = settings.value("recent/file-" + QString::number(i), "").toString();
    //    if (!sFilename.isEmpty()) {
    //        d->m_cRecentAtlasFiles.append(sFilename);
    //    }
    //}
    //createRecentFileActions();

    //if (!d->m_sRecentAtlasFolder.isEmpty()) {
    //    d->m_cDlgLoad->setDirectory(d->m_sRecentAtlasFolder);
    //    d->m_cDlgSaveAs->setDirectory(d->m_sRecentAtlasFolder);
    //}
}


void MainWindow::saveSettings() {
    QSettings settings{"rpgmapper", "rpgmapper"};
    saveSettingsWindow(settings);
    //saveSettingsRecentFiles(settings);
}


void MainWindow::saveSettingsWindow(QSettings & settings) {
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}


void MainWindow::setupDialogs() {

    // TODO
//    QStringList cFileNameFilters;
//    cFileNameFilters << tr("Atlas files [*.atlas] (*.atlas)")
//                     << tr("Any files [*.*] (*)");
//
//    d->m_cDlgAbout = new AboutDialog(this);
//
//    d->m_cDlgLoad = new QFileDialog(this);
//    d->m_cDlgLoad->setFileMode(QFileDialog::ExistingFile);
//    d->m_cDlgLoad->setNameFilters(cFileNameFilters);
//    d->m_cDlgLoad->setAcceptMode(QFileDialog::AcceptOpen);
//    d->m_cDlgLoad->setWindowTitle(tr("Load Atlas file"));
//    d->m_cDlgLoad->setDirectory(d->m_sRecentAtlasFolder);
//
//    d->m_cDlgLog = new LogDialog(this);
//
//    d->m_cDlgMapProperties = new MapPropertiesDialog(this);
//
//    d->m_cDlgSaveAs = new QFileDialog(this);
//    d->m_cDlgSaveAs->setFileMode(QFileDialog::AnyFile);
//    d->m_cDlgSaveAs->setNameFilters(cFileNameFilters);
//    d->m_cDlgSaveAs->setAcceptMode(QFileDialog::AcceptSave);
//    d->m_cDlgSaveAs->setWindowTitle(tr("Save Atlas file"));
//    d->m_cDlgSaveAs->setDirectory(d->m_sRecentAtlasFolder);
}


void MainWindow::showEvent(QShowEvent * cEvent) {

    QMainWindow::showEvent(cEvent);

    static bool bFirstTime = true;
    if (bFirstTime) {

        // ugly hack, since I did not get how Qt saves the visibilty state
        // in the saveState() and restoreState() methods of the QDockWindow childs
        // --> anyone?
// TODO
//        d->ui->acViewMinimap->setChecked(d->ui->dwMiniMap->isVisible());
//        d->ui->acViewStructure->setChecked(d->ui->dwAtlasTree->isVisible());
//        d->ui->acViewTiles->setChecked(d->ui->dwTiles->isVisible());

        bFirstTime = false;
    }
}















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
 * Adds a filename to the list of recent filenames.
 *
 * @param   sFileName       the filename to add
 */
void MainWindow::addRecentFileName(QString const & sFileName) {

    if (sFileName.isEmpty()) {
        return;
    }

    if (!d->m_cRecentAtlasFiles.contains(sFileName)) {
        d->m_cRecentAtlasFiles.push_front(sFileName);
        while (d->m_cRecentAtlasFiles.size() > d->m_nMaximumRecentAtlasFiles) {
            d->m_cRecentAtlasFiles.removeLast();
        }
    }

    QFileInfo cFileInfo(sFileName);
    if (cFileInfo.isFile()) {
        d->m_sRecentAtlasFolder = cFileInfo.absoluteDir().absolutePath();
    }

    createRecentFileActions();
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
 * Empties the sub menu of recent files, but the "Clear List" action.
 */
void MainWindow::clearRecentFileActions() {

    for (auto & cAction : d->ui->mnOpenRecent->actions()) {
        if (cAction != d->ui->acRecentListClear) {
            d->ui->mnOpenRecent->removeAction(cAction);
        }
    }
    for (auto & cAction : d->m_cRecentFileActions) {
        cAction->deleteLater();
    }
    d->m_cRecentFileActions.clear();
}


/**
 * Clear list of recent files.
 */
void MainWindow::clearListOfRecentFiles() {

    for (auto & cAction: d->m_cRecentFileActions) {
        delete cAction;
    }
    d->m_cRecentFileActions.clear();
    d->m_cRecentAtlasFiles.clear();

    enableActions();
}


/**
 * Create list of recent file menu actions.
 */
void MainWindow::createRecentFileActions() {

    clearRecentFileActions();

    for (auto const & sFileName: d->m_cRecentAtlasFiles) {

        auto cRecentFileAction = new QAction(this);
        cRecentFileAction->setObjectName(sFileName);
        cRecentFileAction->setText(sFileName);
        connect(cRecentFileAction, &QAction::triggered, this, &MainWindow::loadRecentFile);

        d->m_cRecentFileActions.push_back(cRecentFileAction);
    }

    d->ui->mnOpenRecent->insertActions(d->ui->acRecentListClear, d->m_cRecentFileActions);
    d->ui->mnOpenRecent->insertSeparator(d->ui->acRecentListClear);

    enableActions();
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
 * Switch enabled state of actions.
 *
 * This method checks the action is enabled or disabled for a series of available actions.
 */
void MainWindow::enableActions() {
    d->ui->acRecentListClear->setEnabled(!d->m_cRecentAtlasFiles.empty());
}


/**
 * Load an atlas.
 */
void MainWindow::load() {

    auto nAnswer = d->m_cDlgLoad->exec();
    if ((nAnswer == 0) || d->m_cDlgSaveAs->selectedFiles().empty()) {
        return;
    }
    loadAtlas(d->m_cDlgLoad->selectedFiles().first());
}


/**
 * Load an atlas from a file.
 *
 * @param   sFileName       the file to load
 */
void MainWindow::loadAtlas(QString const & sFileName) {

    QStringList cLoadLog;
    if (!Controller::instance().load(sFileName, cLoadLog)) {
        d->m_cDlgLog->setWindowTitle(tr("Load atlas failure"));
        d->m_cDlgLog->clear();
        d->m_cDlgLog->setMessage(tr("Failed to load atlas file."));
        d->m_cDlgLog->setLog(cLoadLog);
        d->m_cDlgLog->exec();
    }
    else {
        addRecentFileName(Controller::instance().file().filename());
        resetAtlas();
    }
}


/**
 * Load a recent file.
 */
void MainWindow::loadRecentFile() {

    auto cAction = dynamic_cast<QAction *>(sender());
    if (!cAction) {
        return;
    }

    // we could use cAction->text(). However, Qt automagically adds
    // the shortcut literal '&' to the text, disturbing the file name.
    loadAtlas(cAction->objectName());
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


/**
 * Save the atlas.
 */
void MainWindow::save() {

    if (Controller::instance().file().filename().isEmpty()) {
        saveAs();
        return;
    }
    saveAtlas(Controller::instance().file().filename());
}


/**
 * Save the atlas with a new filename.
 */
void MainWindow::saveAs() {

    auto nAnswer = d->m_cDlgSaveAs->exec();
    if ((nAnswer == 0) || d->m_cDlgSaveAs->selectedFiles().empty()) {
        return;
    }
    saveAtlas(d->m_cDlgSaveAs->selectedFiles().first());
}


/**
 * Save the atlas to a file.
 *
 * @param   sFileName       the file to save the atlas to
 */
void MainWindow::saveAtlas(QString const & sFileName) {

    QStringList cSaveLog;
    if (!Controller::instance().save(sFileName, cSaveLog)) {
        d->m_cDlgLog->setWindowTitle(tr("Save atlas failure"));
        d->m_cDlgLog->clear();
        d->m_cDlgLog->setMessage(tr("Failed to save atlas file."));
        d->m_cDlgLog->setLog(cSaveLog);
        d->m_cDlgLog->exec();
    }
    else {
        addRecentFileName(Controller::instance().file().filename());
    }
}


/**
 * Save the window geometry and states.
 *
 * @param   cSettings       settings instance to save to
 */
void MainWindow::saveSettingsRecentFiles(QSettings & cSettings) {

    cSettings.remove("recent");
    cSettings.setValue("recent/maximum", d->m_nMaximumRecentAtlasFiles);
    cSettings.setValue("recent/folder", d->m_sRecentAtlasFolder);

    int nFileIndex = 0;
    for (auto const & sFilename : d->m_cRecentAtlasFiles){
        cSettings.setValue("recent/file-" + QString::number(++nFileIndex), sFilename);
        if (nFileIndex >= d->m_nMaximumRecentAtlasFiles) {
            break;
        }
    }
}


/**
 * Show about dialog.
 */
void MainWindow::showAboutDialog() {
    d->m_cDlgAbout->exec();
}


/**
 * Shows the coordinates in user world transformation at the statusbar.
 *
 * @param   x   X-coordinate on the map (with origin top/left)
 * @param   y   Y-coordinate on the map (with origin top/left)
 */
void MainWindow::showCoordinates(int x, int y) {

    QString sCoordinates;
    auto cMap = Controller::instance().atlas()->currentMap();
    if (cMap.data() != nullptr) {
        auto cUserCoordinates = cMap->translate(x, y);
        d->m_cWdCoordinates->showCoordinates(cUserCoordinates.m_sX, cUserCoordinates.m_sY);
    }
    else {
        d->m_cWdCoordinates->clear();
    }
}


/**
 * Toggle the minimap window visibility.
 *
 * @param   bView       visibility of window
 */
void MainWindow::visibleMinimap(bool bView) {
    d->ui->dwMiniMap->setVisible(bView);
}


/**
 * Toggle the structure window visibility.
 *
 * @param   bView       visibility of window
 */
void MainWindow::visibleStructure(bool bView) {
    d->ui->dwAtlasTree->setVisible(bView);
}


/**
 * Toggle the tiles window visibility.
 *
 * @param   bView       visibility of window
 */
void MainWindow::visibleTiles(bool bView) {
    d->ui->dwTiles->setVisible(bView);
}


#endif
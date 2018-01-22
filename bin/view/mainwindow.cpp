/*
 * mainwindow.cpp
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

#include <iostream>

// Qt
#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QSettings>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/common_macros.h>
#include <rpgmapper/controller.hpp>
#include "aboutdialog.hpp"
#include "mainwindow.hpp"
#include "structuraltreewidget.hpp"

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

    std::shared_ptr<Ui_mainwindow> ui;                  /**< User interface. */

    QStringList m_cRecentAtlasFiles;                    /**< Recently loaded atlas files. */
    unsigned int m_nMaximumRecentAtlasFiles = 10;       /**< Number of recent files should be remembered. */
    std::list<QAction *> m_cRecentFileActions;          /**< List of recent file actions. */

    AboutDialog * m_cDlgAbout = nullptr;                /**< About RPGMapper dialog. */
    QFileDialog * m_cDlgLoad = nullptr;                 /**< Load file dialog. */
    QFileDialog * m_cDlgSaveAs = nullptr;               /**< SaveAs file dialog. */
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
    statusBar()->setSizeGripEnabled(true);

    setupDialogs();

    connectActions();
    loadSettings();

    d->ui->tabMap->clear();
    d->ui->twAtlas->resetStructure();
    d->ui->twAtlas->selectFirstMap();

    connect(Controller::instance().atlas().data(), &Atlas::changed, this, &MainWindow::changedAtlas);

    enableActions();
    changedAtlas();
}


/**
 * Cnters the window on the desktop with default width and height.
 */
void MainWindow::centerWindow() {

    const int nDefaultWidth = 600;
    const int nDefaultHeight = 400;

    QDesktopWidget * cDesktop = dynamic_cast<QApplication *>(QApplication::instance())->desktop();
    int nX = (cDesktop->width() - nDefaultWidth) / 2;
    int nY = (cDesktop->height() - nDefaultHeight) / 2;

    resize(QSize(nDefaultWidth, nDefaultHeight));
    move(QPoint(nX, nY));
}


/**
 * The atlas changed.
 */
void MainWindow::changedAtlas() {

    auto cAtlas = Controller::instance().atlas();
    QString sModifiedMarker = cAtlas->modified() ? "*" : "";

    QString sTitle = cAtlas->name() + sModifiedMarker + " - RPGMapper V" + VERSION;
    setWindowTitle(sTitle);
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
 * Handle close event.
 *
 * @param   cEvent      the event passed
 */
void MainWindow::closeEvent(QCloseEvent* cEvent) {

    QSettings cSettings{"rpgmapper", "rpgmapper"};

    cSettings.setValue("geometry", saveGeometry());
    cSettings.setValue("windowState", saveState());

    cSettings.remove("recent");
    cSettings.setValue("recent/maximum", d->m_nMaximumRecentAtlasFiles);
    unsigned int nFileIndex = 0;
    for (auto const & sFilename : d->m_cRecentAtlasFiles){
        if (sFilename.isEmpty()) {
            break;
        }
        cSettings.setValue("recent/file-" + QString::number(++nFileIndex), sFilename);
        if (nFileIndex >= d->m_nMaximumRecentAtlasFiles) {
            break;
        }
    }

    QMainWindow::closeEvent(cEvent);
}


/**
 * Connects all action signals for this MainWindow.
 */
void MainWindow::connectActions() {

    connect(d->ui->acAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(d->ui->acOpen, &QAction::triggered, this, &MainWindow::load);
    connect(d->ui->acQuit, &QAction::triggered, this, &MainWindow::close);
    connect(d->ui->acRecentListClear, &QAction::triggered, this, &MainWindow::clearListOfRecentFiles);
    connect(d->ui->acSave, &QAction::triggered, this, &MainWindow::save);
    connect(d->ui->acSaveAs, &QAction::triggered, this, &MainWindow::saveAs);

    connect(d->ui->twAtlas, &StructuralTreeWidget::selectedMap, d->ui->tabMap, &MapTabWidget::selectMap);
}


/**
 * Create list of recent file menu actions.
 */
void MainWindow::createRecentFileActions() {

    for (auto & cAction: d->m_cRecentFileActions) {
        delete cAction;
    }
    d->m_cRecentFileActions.clear();

    for (auto const & sFileName: d->m_cRecentAtlasFiles) {

        auto cRecentFileAction = new QAction(this);
        cRecentFileAction->setObjectName(sFileName);
        cRecentFileAction->setText(sFileName);
        connect(cRecentFileAction, &QAction::triggered, this, &MainWindow::loadRecentFile);

        d->m_cRecentFileActions.push_back(cRecentFileAction);
        d->ui->mnOpenRecent->addAction(cRecentFileAction);
    }
    enableActions();
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
    d->m_cDlgLoad->exec();
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
    UNUSED QString sFileToLoad = cAction->objectName();
    // TODO: load file
}


/**
 * Load the settings.
 */
void MainWindow::loadSettings() {

    QSettings cSettings{"rpgmapper", "rpgmapper"};

    if (cSettings.contains("geometry")) {
        restoreGeometry(cSettings.value("geometry").toByteArray());
    }
    else {
        centerWindow();
    }
    restoreState(cSettings.value("windowState").toByteArray());

    d->m_nMaximumRecentAtlasFiles = cSettings.value("recent/maximum", 10).toUInt();
    d->m_cRecentAtlasFiles.clear();
    for (unsigned int i = 0; i < d->m_nMaximumRecentAtlasFiles; ++i) {
        QString sFilename = cSettings.value("recent/file-" + QString::number(i), "").toString();
        if (!sFilename.isEmpty()) {
            d->m_cRecentAtlasFiles.append(sFilename);
        }
    }
    createRecentFileActions();
}


/**
 * Save the atlas.
 */
void MainWindow::save() {

    if (Controller::instance().file().filename().isEmpty()) {
        saveAs();
        return;
    }
}


/**
 * Save the atlas with a new filename.
 */
void MainWindow::saveAs() {
    d->m_cDlgSaveAs->exec();
}


/**
 * Setup the internal dialogs.
 */
void MainWindow::setupDialogs() {

    QStringList cFileNameFilters;
    cFileNameFilters << tr("Atlas files [*.atlas] (*.atlas)")
                     << tr("Any files [*.*] (*)");

    d->m_cDlgAbout = new AboutDialog(this);

    d->m_cDlgLoad = new QFileDialog(this);
    d->m_cDlgLoad->setFileMode(QFileDialog::ExistingFile);
    d->m_cDlgLoad->setNameFilters(cFileNameFilters);
    d->m_cDlgLoad->setAcceptMode(QFileDialog::AcceptOpen);
    d->m_cDlgLoad->setWindowTitle(tr("Load Atlas file"));

    d->m_cDlgSaveAs = new QFileDialog(this);
    d->m_cDlgSaveAs->setFileMode(QFileDialog::AnyFile);
    d->m_cDlgSaveAs->setNameFilters(cFileNameFilters);
    d->m_cDlgSaveAs->setAcceptMode(QFileDialog::AcceptSave);
    d->m_cDlgSaveAs->setWindowTitle(tr("Save Atlas file"));
}


/**
 * Show about dialog.
 */
void MainWindow::showAboutDialog() {
    d->m_cDlgAbout->exec();
}

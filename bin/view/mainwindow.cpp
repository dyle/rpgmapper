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

// Qt
#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QSettings>

// rpgmapper
#include <rpgmapper/controller.hpp>
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

    std::shared_ptr<Ui_mainwindow> ui;          /**< User interface. */

    QFileDialog * m_cDlgLoad;                   /**< Load file dialog. */
    QFileDialog * m_cDlgSaveAs;                 /**< SaveAs file dialog. */
};


}
}


// ------------------------------------------------------------
// code


/**
 * ctor
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
 * Connects all action signals for this MainWindow.
 */
void MainWindow::connectActions() {

    connect(d->ui->acOpen, &QAction::triggered, this, &MainWindow::load);
    connect(d->ui->acSave, &QAction::triggered, this, &MainWindow::save);
    connect(d->ui->acSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(d->ui->acQuit, &QAction::triggered, this, &MainWindow::close);

    connect(d->ui->twAtlas, &StructuralTreeWidget::selectedMap, d->ui->tabMap, &MapTabWidget::selectMap);
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

    QMainWindow::closeEvent(cEvent);
}


/**
 * Load an atlas.
 */
void MainWindow::load() {
    d->m_cDlgLoad->exec();
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
}


/**
 * Save the atlas.
 */
void MainWindow::save() {

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
    cFileNameFilters << tr("Atlas files (*.atlas)")
                     << tr("Any files (*)");

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

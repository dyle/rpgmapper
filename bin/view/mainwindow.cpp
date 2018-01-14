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
#include <QPixmapCache>
#include <QSettings>

// rpgmapper
#include <rpgmapper/ctrl/controller.hpp>
#include "mainwindow.hpp"

#include "ui_mainwindow.h"


using namespace rpgmapper::ctrl;
using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl


/**
 * Add the atlas to the structural tree view
 *
 * @param   cTWAtlas        the QTreeWidget structural widget
 */
static void appendStructureAtlas(QTreeWidget * cTWAtlas);


/**
 * Add a map structural tree view
 *
 * @param   cTIRegion       the QTreeWidgetItem holding the region item
 * @param   cMap            the map to add
 * @return  The QTreeWidgetItem created
 */
static QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, Map const & cMap);


/**
 * Add a region structural tree view
 *
 * @param   cTIAtlas        the QTreeWidgetItem holding the atlas item
 * @param   cRegion         the region to add
 * @return  The QTreeWidgetItem created
 */
static QTreeWidgetItem * appendStructureRegion(QTreeWidgetItem * cTWAtlas, Region const & cRegion);


// ------------------------------------------------------------
// code


/**
 * ctor
 */
MainWindow::MainWindow() : QMainWindow() {

    ui = std::make_shared<Ui_mainwindow>();
    ui->setupUi(this);
    statusBar()->setSizeGripEnabled(true);

    loadSettings();
    reset();
}


/**
 * centers the window on the desktop with default width and height
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
 * handle close event
 *
 * @param   cEvent      the event passed
 */
void MainWindow::closeEvent(QCloseEvent* cEvent) {

    QSettings cSettings("rpgmapper", "rpgmapper");

    cSettings.setValue("geometry", saveGeometry());
    cSettings.setValue("windowState", saveState());

    QMainWindow::closeEvent(cEvent);
}


/**
 * load the settings
 */
void MainWindow::loadSettings() {

    QSettings cSettings("rpgmapper", "rpgmapper");

    if (cSettings.contains("geometry")) {
        restoreGeometry(cSettings.value("geometry").toByteArray());
    }
    else {
        centerWindow();
    }
    restoreState(cSettings.value("windowState").toByteArray());
}


/**
 * Clear all and apply the current atlas to the widgets.
 */
void MainWindow::reset() {
    ui->twAtlas->clear();
    appendStructureAtlas(ui->twAtlas);
}


/**
 * Add the atlas to the structural tree view
 *
 * @param   cTWAtlas        the QTreeWidget structural widget
 */
void appendStructureAtlas(QTreeWidget * cTWAtlas) {

    QTreeWidgetItem * cTWItem = nullptr;
    QPixmap cPixmap;
    QStringList sl;

    sl << Controller::instance().atlas().name() << "atlas" << "";
    cTWItem = new QTreeWidgetItem(sl);
    QPixmapCache::find("atlas", &cPixmap);
    cTWItem->setIcon(0, cPixmap);
    cTWAtlas->insertTopLevelItem(0, cTWItem);

    for (auto const & cRegion: Controller::instance().atlas().regions()) {
        auto cTWRegion = appendStructureRegion(cTWItem, cRegion.second);
        cTWRegion->setExpanded(true);
    }

    cTWItem->setExpanded(true);
}


/**
 * Add a map structural tree view
 *
 * @param   cTIRegion       the QTreeWidgetItem holding the region item
 * @param   cMap            the map to add
 * @return  The QTreeWidgetItem created
 */
QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, Map const & cMap) {

    QPixmap cPixmap;
    QStringList sl;

    sl << cMap.name() << "map" << QString::number(cMap.id());
    auto cTWMapItem = new QTreeWidgetItem(cTWRegion, sl);
    QPixmapCache::find("map", &cPixmap);
    cTWMapItem->setIcon(0, cPixmap);

    return cTWMapItem;
}


/**
 * Add a region structural tree view
 *
 * @param   cTIAtlas        the QTreeWidgetItem holding the atlas item
 * @param   cRegion         the region to add
 * @return  The QTreeWidgetItem created
 */
QTreeWidgetItem * appendStructureRegion(QTreeWidgetItem * cTWAtlas, Region const & cRegion) {

    QPixmap cPixmap;
    QStringList sl;

    sl << cRegion.name() << "region" << QString::number(cRegion.id());
    auto cTWRegionItem = new QTreeWidgetItem(cTWAtlas, sl);
    QPixmapCache::find("region", &cPixmap);
    cTWRegionItem->setIcon(0, cPixmap);

    for (auto const & cMap: cRegion.maps()) {
        auto cTWMap = appendStructureMap(cTWRegionItem, cMap.second);
        cTWMap->setExpanded(true);
    }
    return cTWRegionItem;
}

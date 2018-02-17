/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "mainwindow_impl.hpp"

using namespace rpgmapper::view;


MainWindow::Impl::Impl(MainWindow * mainWindow) : mainWindow(mainWindow) {

    if (mainWindow == nullptr) {
        throw std::runtime_error("mainWindow must not be nullptr.");
    }

    ui = std::make_shared<Ui_mainwindow>();
    ui->setupUi(mainWindow);

    ui->mapTabWidget->clear();
    ui->atlasTreeWidget->resetStructure();
    ui->atlasTreeWidget->selectFirstMap();
    ui->atlasTreeNewMapToolButton->setDefaultAction(ui->actionCreateNewMap);
    ui->atlasTreeNewRegionToolButton->setDefaultAction(ui->actionCreateNewRegion);
    ui->atlasTreeDeleteMapToolButton->setDefaultAction(ui->actionDeleteMap);
    ui->atlasTreeDeleteRegionToolButton->setDefaultAction(ui->actionDeleteRegion);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <chrono>
#include <thread>

#include <QApplication>
#include <QTimer>

#include "startupdialog.hpp"
#include "ui_startupdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


StartupDialog::StartupDialog(MainWindow * mainWindow)
        : QDialog{nullptr, Qt::Window | Qt::FramelessWindowHint},
          mainWindow{mainWindow} {
    
    ui = std::make_shared<Ui_startupDialog>();
    ui->setupUi(this);
    
    ui->labelWork->setText(tr("Loading RPGMapper resources..."));
    ui->loadingProgress->setValue(0);
    
    loader = new ResourceLoader{this};
    connect(loader, &ResourceLoader::loading, this, &StartupDialog::loadingResource);
    connect(loader, &ResourceLoader::done, this, &StartupDialog::resourceLoaded);
    
    QTimer::singleShot(0, this, &StartupDialog::startup);
}


void StartupDialog::doneGood() {
    mainWindow->show();
    close();
}


void StartupDialog::doneFailed() {
    close();
    QApplication::exit(1);
}


void StartupDialog::loadingResource(ResourceLoader::ResourceLoadingEvent const & loadingEvent) {
    ui->labelWork->setText(tr("Loading: %1...").arg(loadingEvent.resourceFile));
    int progressValue = loadingEvent.maxSteps != 0 ? (loadingEvent.step * 100) / loadingEvent.maxSteps : 0;
    ui->loadingProgress->setValue(progressValue);
}


void StartupDialog::resourceLoaded() {
    if (loader->isSuccess()) {
        doneGood();
    }
    else {
        doneFailed();
    }
}


void StartupDialog::startup() {
    loader->load(log);
}

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <QApplication>
#include <QMessageBox>
#include <QTimer>

#include "logdialog.hpp"
#include "startupdialog.hpp"
#include "ui_startupdialog.h"

using namespace rpgmapper::model::resource;
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
    mainWindow->applyResources();
    mainWindow->show();
    close();
}


void StartupDialog::doneFailed() {
    
    auto question = tr("RPGMapper could not start.\nDo you want to see the log?");
    auto answer = QMessageBox::question(this, tr("Startup failure"), question);
    if (answer == QMessageBox::Yes) {
        LogDialog logDialog{this};
        logDialog.setMessage(tr("Failed to start RPGMapper"));
        logDialog.setLog(log);
        logDialog.exec();
    }
    
    close();
    QApplication::exit(1);
}


void StartupDialog::loadingResource(ResourceLoader::LoadingEvent const & loadingEvent) {
    ui->labelWork->setText(tr("Loading: %1...").arg(loadingEvent.resourceFile));
    int progressValue = loadingEvent.maxSteps != 0 ? (loadingEvent.step * 100) / loadingEvent.maxSteps : 0;
    ui->loadingProgress->setValue(progressValue);
}


void StartupDialog::resourceLoaded() {
    loader->isSuccess() ? doneGood() : doneFailed();
}


void StartupDialog::startup() {
    loader->load(log);
}

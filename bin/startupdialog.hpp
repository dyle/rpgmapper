/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_STARTUPDIALOG_HPP
#define RPGMAPPER_VIEW_STARTUPDIALOG_HPP

#include <memory>

#include <QDialog>

#include "mainwindow.hpp"


// fwd
class Ui_startupDialog;


namespace rpgmapper {
namespace view {


/**
 * This dialog shows something startup the rpgmapper application.
 */
class StartupDialog : public QDialog {

    Q_OBJECT
    
    std::shared_ptr<Ui_startupDialog> ui;         /**< The User Interface as created by the uic. */
    MainWindow * mainWindow = nullptr;

public:
    
    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit StartupDialog(MainWindow * mainWindow);
    
private slots:
    
    /**
     * We have finished loading and all is good.
     */
    void doneGood();
    
    /**
     * We have finished loading and failed.
     */
    void doneFailed();
    
    /**
     * Does the startup phase.
     */
    void startup();
    
};


}
}


#endif

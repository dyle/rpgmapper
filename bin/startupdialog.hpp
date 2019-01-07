/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_STARTUPDIALOG_HPP
#define RPGMAPPER_VIEW_STARTUPDIALOG_HPP

#include <memory>

#include <QDialog>
#include <QStringList>

#include <rpgmapper/resource/resource_loader.hpp>

#include "mainwindow.hpp"

// fwd
class Ui_startupDialog;


namespace rpgmapper::view {


/**
 * This dialog shows something startup the rpgmapper application.
 */
class StartupDialog : public QDialog {

    Q_OBJECT
    
    std::shared_ptr<Ui_startupDialog> ui;        /**< The User Interface as created by the uic. */
    MainWindow * mainWindow;                     /**< The mainwindow to show, when we are done. */
    QStringList log;                             /**< The log of action doing startup. */
    
    /**
     * The resource loader used.
     */
    rpgmapper::model::resource::ResourceLoader * loader;

public:
    
    /**
     * Constructor.
     *
     * @param   mainWindow      the mainwindow to show once we've finished
     */
    explicit StartupDialog(MainWindow * mainWindow);
    
    /**
     * Gets the log done, while starting up.
     */
    QStringList const & getLog() const {
        return log;
    }
    
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
     * We are currently loading a specific resource.
     *
     * @param   loadingEvent        the loading event.
     */
    void loadingResource(rpgmapper::model::resource::ResourceLoader::LoadingEvent const & loadingEvent);
    
    /**
     * Does the startup phase.
     */
    void startup();
    
    /**
     * Called when the resources have been loaded.
     */
    void resourceLoaded();
};


}


#endif

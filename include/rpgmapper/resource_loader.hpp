/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_LOADER_HPP
#define RPGMAPPER_MODEL_RESOURCE_LOADER_HPP

#include <QObject>
#include <QString>
#include <QStringList>


namespace rpgmapper {
namespace model {


/**
 * The resource loader class loads the system and user defined resources.
 */
class ResourceLoader : public QObject {

    Q_OBJECT
    
    QStringList userFolders;        /**< List of paths where user resources are may located. */
    bool success = false;           /**< Success of loading the resources flag. */

public:
    
    /**
     * This structure defines the current loading step.
     */
    struct ResourceLoadingEvent {
        QString resourceFile;           /**< The current file which we are about to load. */
        int step = 0;                   /**< Current resource file step. */
        int maxSteps = 0;               /**< Maximum steps expected. */
    };
    
    /**
     * Constructor.
     *
     * @param   parent      Parent QObject
     */
    explicit ResourceLoader(QObject * parent);
    
    /**
     * Returns the list of user folders.
     *
     * @return  the list of user folders searched.
     */
    QStringList const & getUserFolders() const {
        return userFolders;
    }
    
    /**
     * Checks if the loading of the resources has been successful.
     *
     * @return  success of resource loading.
     */
    bool isSuccess() const {
        return success;
    }

    /**
     * Starts loading resources.
     *
     * @param   log         a list of log entries to be filled.
     */
    void load(QStringList & log);

    /**
     * Sets the list of user folders to search.
     *
     * @param   folders     the list where we expect user defined resources
     */
    void setUserFolders(QStringList const & folders) {
        userFolders = folders;
    }
    
signals:
    
    /**
     * We finished loading all stuff.
     */
    void done();
    
    /**
     * What we are current about to load.
     *
     * @param   loadingEvent        the loading we are attempting.
     */
    void loading(ResourceLoadingEvent const & loadingEvent);
};


}
}


#endif

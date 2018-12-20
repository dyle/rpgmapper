/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_LOADER_HPP
#define RPGMAPPER_MODEL_RESOURCE_LOADER_HPP

#include <list>
#include <tuple>

#include <QObject>
#include <QString>
#include <QStringList>

#include <rpgmapper/resource_collection_pointer.hpp>


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
     * A ResourceFileCollection holds (resourcefolder, resourcefile) tuples.
     */
    using FileCollection = std::list<std::tuple<QString, QString>>;
    
    /**
     * This structure defines the current loading step.
     */
    struct LoadingEvent {
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
    
private:
    
    /**
     * Loads the resources.
     *
     * @param   fileCollection      the list of found files to load.
     * @param   collection          the resource collection to fill
     * @param   log                 the log of actions.
     */
    void loadResources(FileCollection const & fileCollection, ResourceCollectionPointer collection, QStringList & log);
    
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
    void loading(LoadingEvent const & loadingEvent);
};


}
}


#endif

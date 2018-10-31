/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SESSION_HPP
#define RPGMAPPER_MODEL_SESSION_HPP

#include <QFile>
#include <QSharedPointer>

#include <rpgmapper/command/processor.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/resource_db.hpp>


namespace rpgmapper {
namespace model {


/**
 * A Session object holds everything for a current system snapshot session of a user.
 */
class Session : public QObject {

    Q_OBJECT
    
public:
    
    struct resources_t {
        QSharedPointer<rpgmapper::model::ResourceDB> local;       /**< Atlas own resources. */
        QSharedPointer<rpgmapper::model::ResourceDB> system;      /**< Resources loaded from system files. */
        QSharedPointer<rpgmapper::model::ResourceDB> user;        /**< User specific Resources. */
    };
    
private:
    
    QSharedPointer<rpgmapper::model::Atlas> atlas;                          /**< The atlas of the session. */
    std::map<QString, QSharedPointer<rpgmapper::model::Map>> maps;          /**< All maps on the atlas. */
    std::map<QString, QSharedPointer<rpgmapper::model::Region>> regions;    /**< All regions on the atlas. */
    
    QString currentMapName;            /**< Current selected map. */
    QString currentRegionName;         /**< Current selected region. */
    
    resources_t resources;             /**< All resources. */
    
    /**
     * All loaded resources loaded from system files.
     */
    static QSharedPointer<rpgmapper::model::ResourceDB> systemResources;
    
    /**
     * All loaded resources loaded from user files.
     */
    static QSharedPointer<rpgmapper::model::ResourceDB> userResources;

    /**
     * This instance operates changes on the atlas.
     */
    QSharedPointer<rpgmapper::model::command::Processor> commandProcessor;
    
    QString fileName;               /**< Filename of the atlas loaded or recently saved. */

public:
    
    /**
     * Destructor.
     */
    ~Session() override = default;
    
    /**
     * Creates a new map.
     * @param   mapName         Name of the new map.
     * @param   regionName      Name of the region to create map in.
     * @return  the newly created map.
     */
    QSharedPointer<rpgmapper::model::Map> & createMap(QString mapName, QString regionName);

    /**
     * Creates a new region.
     *
     * @param   name        The name of the new region.
     * @return  the new region.
     */
    QSharedPointer<rpgmapper::model::Region> & createRegion(QString name);
    
    /**
     * Deletes a map.
     *
     * @param   mapName     The map to delete.
     */
    void deleteMap(QString mapName);
    
    /**
     * Deletes a region.
     *
     * @param   regionName  The region to delete.
     */
    void deleteRegion(QString regionName);
    
    /**
     * Finds a specific map by name (convenient method).
     *
     * @param   name        name of the map to search.
     * @return  the found map (maybe invalid map).
     */
    QSharedPointer<rpgmapper::model::Map> findMap(QString name);
    
    /**
     * Finds a specific map by name (convenient method) (const version).
     *
     * @param   name        name of the map to search.
     * @return  the found map (maybe invalid map).
     */
    QSharedPointer<rpgmapper::model::Map> const findMap(QString name) const;
    
    /**
     * Finds a specific region by name (convenient method).
     *
     * @param   name        name of the region to search.
     * @return  the found region (maybe invalid region).
     */
    QSharedPointer<rpgmapper::model::Region> findRegion(QString name);
    
    /**
     * Finds a specific region by name (convenient method) (const version).
     *
     * @param   name        name of the region to search.
     * @return  the found region (maybe invalid region).
     */
    QSharedPointer<rpgmapper::model::Region> const findRegion(QString name) const;
    
    /**
     * Collects all map names (conventient method).
     *
     * @return  all known map names.
     */
    std::set<QString> getAllMapNames() const;
    
    /**
     * Collects all regions names (conventient method).
     *
     * @return  all known regions names.
     */
    std::set<QString> getAllRegionNames() const;
    
    /**
     * Gets the atlas of the current session.
     *
     * @return  the atlas of the session.
     */
    QSharedPointer<rpgmapper::model::Atlas> & getAtlas() {
        return atlas;
    }
    
    /**
     * Gets the atlas of the current session (const version).
     *
     * @return  the atlas of the session.
     */
    QSharedPointer<rpgmapper::model::Atlas> const & getAtlas() const {
        return atlas;
    }
    
    /**
     * Gets the command processor of the session.
     *
     * @return  the command processor of this session.
     */
    QSharedPointer<rpgmapper::model::command::Processor> & getCommandProzessor() {
        return commandProcessor;
    }
    
    /**
     * Gets the command processor of the session (const version).
     *
     * @return  the command processor of this session.
     */
    QSharedPointer<rpgmapper::model::command::Processor> const & getCommandProzessor() const {
        return commandProcessor;
    }
    
    /**
     * Gets the name of the current selected map.
     *
     * @return  the name of the current selected map of the session.
     */
    QString getCurrentMapName() const {
        return currentMapName;
    }
    
    /**
     * Gets the name of the current selected region.
     *
     * @return  the name of the current selected region of the session.
     */
    QString getCurrentRegionName() const {
        return currentRegionName;
    }
    
    /**
     * Gets the current session of the user.
     *
     * @return  The current session.
     */
    static QSharedPointer<Session> getCurrentSession();
    
    /**
     * Gets the file name of the atlas file loaded (or saved recently).
     *
     * @return  the file name associated with the current atlas.
     */
    QString getFileName() {
        return fileName;
    }

    /**
     * Returns all known maps.
     *
     * @return  all maps of the atlas.
     */
    std::map<QString, QSharedPointer<rpgmapper::model::Map>> const & getMaps() const {
        return maps;
    }
    
    /**
     * Returns all known regions.
     *
     * @return  all regions of the atlas.
     */
    std::map<QString, QSharedPointer<rpgmapper::model::Region>> const & getRegions() const {
        return regions;
    }
    
    /**
     * Gets the resources known by the session.
     *
     * @return  all the resources known by the system.
     */
    resources_t & getResources() {
        return resources;
    }
    
    /**
     * Gets the resources known by the session (const version).
     *
     * @return  all the resources known by the system.
     */
    resources_t const & getResources() const {
        return resources;
    }
    
    /**
     * Returns true, of the atlas has changed since last save.
     *
     * @return  true, if the atlas changed.
     */
    bool isModified() const;
    
    /**
     * Inits a new session.
     *
     * [Factory]
     *
     * @return  a new initial session.
     */
    static QSharedPointer<Session> init();
    
    
    /**
     * Inserts an existing map into the set of known maps.
     *
     * @param   map     the map to insert.
     */
    void insertMap(QSharedPointer<Map> map);
    
    
    /**
     * Loads a session from an atlas file fromm disk.
     *
     * @param   session     the loaded session.
     * @param   file        the file to load from.
     * @param   log         Protocol of operations.
     * @return  true, if successfully loaded.
     */
    static bool load(QSharedPointer<Session> & session, QFile & file, QStringList & log);
    
    /**
     * Selects a new current map.
     *
     * @param   name        the name of the new selected map.
     */
    void selectMap(QString name);
    
    /**
     * Selects a new current region.
     *
     * @param   name        the name of the new selected region.
     */
    void selectRegion(QString name);
    
    /**
     * Saves the current session to an atlas file on disk.
     *
     * @param   file        the file to save to.
     * @param   log         Protocol of operations.
     * @return  true, if successfully saved.
     */
    bool save(QFile & file, QStringList & log);
    
signals:
    
    /**
     * A command has been executed by the processor.
     */
    void commandExecuted();

    /**
     * A new map has been created.
     *
     * @param   mapName     the name of the map created.
     */
    void mapCreated(QString mapName);
    
    /**
     * A map has been deleted.
     *
     * @param   mapName     the name of the map deleted.
     */
    void mapDeleted(QString mapName);
    
    /**
     * A new map has been selected.
     *
     * @param   mapName     the name of the new map selected.
     */
    void mapSelected(QString mapName);
    
    /**
     * A new region has been created.
     *
     * @param   regionName     the name of the region created.
     */
    void regionCreated(QString regionName);
    
    /**
     * A region has been deleted.
     *
     * @param   regionName     the name of the region deleted.
     */
    void regionDeleted(QString regionName);
    
    /**
     * A new region has been selected.
     *
     * @param   regionName  the name of the new region selected.
     */
    void regionSelected(QString regionName);
    
private:
    
    /**
     * Constructor
     */
    Session();
};
    

}
}


#endif

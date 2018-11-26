/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SESSION_HPP
#define RPGMAPPER_MODEL_SESSION_HPP

#include <map>
#include <set>

#include <QFile>
#include <QSharedPointer>

#include <rpgmapper/command/processor_pointer.hpp>
#include <rpgmapper/atlas_pointer.hpp>
#include <rpgmapper/map_pointer.hpp>
#include <rpgmapper/region_pointer.hpp>
#include <rpgmapper/resource_db_pointer.hpp>
#include <rpgmapper/session_pointer.hpp>


namespace rpgmapper {
namespace model {


/**
 * A Session holds everything for a current system snapshot session of a user.
 */
class Session : public QObject {

    Q_OBJECT
    
public:
    
    struct ResourceCollection {
        ResourceDBPointer local;        /**< Atlas own resources. */
        ResourceDBPointer system;       /**< Resources loaded from system files. */
        ResourceDBPointer user;         /**< User specific Resources. */
    };
    
private:
    
    AtlasPointer atlas;                /**< The atlas of the session. */
    
    QString currentMapName;            /**< Current selected map. */
    QString currentRegionName;         /**< Current selected region. */
    
    ResourceCollection resources;      /**< All resources. */
    
    /**
     * All loaded resources loaded from system files.
     */
    static ResourceDBPointer systemResources;
    
    /**
     * All loaded resources loaded from user files.
     */
    static ResourceDBPointer userResources;

    /**
     * This instance operates changes on the atlas.
     */
    command::ProcessorPointer commandProcessor;
    
    QString fileName;               /**< Filename of the atlas loaded or recently saved. */

public:
    
    /**
     * Destructor.
     */
    ~Session() override = default;
    
    /**
     * Suggests a new map name.
     *
     * @return  a name suitable for a new map.
     */
    QString createNewMapName() const;

    /**
     * Suggests a new region name.
     *
     * @return  a name suitable for a new region.
     */
    QString createNewRegionName() const;

    /**
     * Finds a specific map by name (convenient method).
     *
     * @param   name        name of the map to search.
     * @return  the found map (maybe invalid map).
     */
    MapPointer findMap(QString name);
    
    /**
     * Finds a specific map by name (convenient method) (const version).
     *
     * @param   name        name of the map to search.
     * @return  the found map (maybe invalid map).
     */
    MapPointer const findMap(QString name) const;
    
    /**
     * Finds a specific region by name (convenient method).
     *
     * @param   name        name of the region to search.
     * @return  the found region (maybe invalid region).
     */
    RegionPointer findRegion(QString name);
    
    /**
     * Finds a specific region by name (convenient method) (const version).
     *
     * @param   name        name of the region to search.
     * @return  the found region (maybe invalid region).
     */
    RegionPointer const findRegion(QString name) const;
    
    /**
     * Collects all map names (convenient method).
     *
     * @return  all known map names with their regions.
     */
    std::map<QString, QString> getAllMapNames() const;
    
    /**
     * Collects all regions names (convenient method).
     *
     * @return  all known regions names with their maps.
     */
    std::map<QString, std::set<QString>> getAllRegionNames() const;
    
    /**
     * Gets the atlas of the current session.
     *
     * @return  the atlas of the session.
     */
    AtlasPointer & getAtlas() {
        return atlas;
    }
    
    /**
     * Gets the atlas of the current session (const version).
     *
     * @return  the atlas of the session.
     */
    AtlasPointer const & getAtlas() const {
        return atlas;
    }
    
    /**
     * Gets the command processor of the session.
     *
     * @return  the command processor of this session.
     */
    command::ProcessorPointer & getCommandProcessor() {
        return commandProcessor;
    }
    
    /**
     * Gets the command processor of the session (const version).
     *
     * @return  the command processor of this session.
     */
    command::ProcessorPointer const & getCommandProcessor() const {
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
    static SessionPointer getCurrentSession();
    
    /**
     * Gets the file name of the atlas file loaded (or saved recently).
     *
     * @return  the file name associated with the current atlas.
     */
    QString getFileName() const {
        return fileName;
    }
    
    /**
     * Gets the region name of a given map.
     *
     * @param   mapName     the name of the map.
     * @return  the name of the region the map belongs to (or QString::null).
     */
    QString getRegionOfMap(QString mapName) const;

    /**
     * Gets the resources known by the session.
     *
     * @return  all the resources known by the system.
     */
    ResourceCollection & getResources() {
        return resources;
    }
    
    /**
     * Gets the resources known by the session (const version).
     *
     * @return  all the resources known by the system.
     */
    ResourceCollection const & getResources() const {
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
    static SessionPointer init();
    
    /**
     * Loads a session from an atlas file fromm disk.
     *
     * @param   session     the loaded session.
     * @param   file        the file to load from.
     * @param   log         Protocol of operations.
     * @return  true, if successfully loaded.
     */
    static bool load(SessionPointer & session, QFile & file, QStringList & log);
    
    /**
     * Saves the current session to an atlas file on disk.
     *
     * @param   file        the file to save to.
     * @param   log         Protocol of operations.
     * @return  true, if successfully saved.
     */
    bool save(QFile & file, QStringList & log);
    
    /**
     * Selects the atlas.
     *
     * This effectively deselects any region or map.
     */
    void selectAtlas();
    
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
     * Sets a new current session.
     * @param   session     the new current session
     */
    static void setCurrentSession(SessionPointer session);
    
    
signals:
    
    /**
     * The atlas has been selected (and thus no region nor map).
     */
    void selectedAtlas();
    
    /**
     * A new map has been selected.
     *
     * @param   name        name of the new selected map.
     */
    void selectedMap(QString name);
    
    /**
     * A new region has been selected.
     *
     * @param   name        name of the new selected region.
     */
    void selectedRegion(QString name);
    
private:
    
    /**
     * Constructor
     */
    Session();
    
    /**
     * Loads all system resources into the system resource DB.
     */
    static void loadSystemResourceDB();
    
    /**
     * Loads all user defined resources into the user resource DB.
     */
    static void loadUserResourceDB();
};
    

}
}


#endif

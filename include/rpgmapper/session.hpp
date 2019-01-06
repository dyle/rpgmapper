/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SESSION_HPP
#define RPGMAPPER_MODEL_SESSION_HPP

#include <map>
#include <set>

#include <QFile>
#include <QSharedPointer>

#include <rpgmapper/command/processor_pointer.hpp>
#include <rpgmapper/tile/tile_pointer.hpp>
#include <rpgmapper/atlas_pointer.hpp>
#include <rpgmapper/map_pointer.hpp>
#include <rpgmapper/region_pointer.hpp>
#include <rpgmapper/session_pointer.hpp>


namespace rpgmapper {
namespace model {


/**
 * A Session holds everything for a current system snapshot session of a user.
 */
class Session : public QObject {

    Q_OBJECT
    
private:
    
    AtlasPointer atlas;                /**< The atlas of the session. */
    
    QString currentMapName;            /**< Current selected map. */
    QString currentRegionName;         /**< Current selected region. */
    
    /**
     * This instance operates changes on the atlas.
     */
    command::ProcessorPointer commandProcessor;
    
    QString fileName;                   /**< Filename of the atlas loaded or recently saved. */
    
    rpgmapper::model::tile::TilePointer currentTile;        /**< Current selected tile. */
    rpgmapper::model::tile::TilePointer lastAppliedTile;    /**< The tile the user has just applied. */

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
     * Returns the currently selected tile.
     *
     * @return  the current selected tile.
     */
    rpgmapper::model::tile::TilePointer getCurrentTile() {
        return currentTile;
    }
    
    /**
     * Returns the currently selected tile (const version).
     *
     * @return  the current selected tile.
     */
    rpgmapper::model::tile::TilePointer const getCurrentTile() const {
        return currentTile;
    }
    
    /**
     * Gets the file name of the atlas file loaded (or saved recently).
     *
     * @return  the file name associated with the current atlas.
     */
    QString getFileName() const {
        return fileName;
    }
    
    /**
     * Returns the tile the user applied last.
     *
     * @return  the last tile the user applied.
     */
    rpgmapper::model::tile::TilePointer const getLastAppliedTile() const {
        return lastAppliedTile;
    }
    
    /**
     * Gets the region name of a given map.
     *
     * @param   mapName     the name of the map.
     * @return  the name of the region the map belongs to (or QString::null).
     */
    QString getRegionOfMap(QString mapName) const;
    
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
    
    /**
     * Sets a new current tile.
     *
     * @param   tile        the new current tile.
     */
    void setCurrentTile(rpgmapper::model::tile::TilePointer & tile);
    
    /**
     * Sets the last applied tile.
     *
     * @param   tile        the last applied tile.
     */
    void setLastAppliedTile(rpgmapper::model::tile::TilePointer & tile);

signals:
    
    /**
     * The user applied just a tile to a map.
     */
    void newLastAppliedTile();
    
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
    
    /**
     * A new tile has been selected as new current tile.
     */
    void selectedTile();
    
private:
    
    /**
     * Constructor
     */
    Session();
};
    

}
}


#endif

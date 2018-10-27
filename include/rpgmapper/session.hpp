/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SESSION_HPP
#define RPGMAPPER_MODEL_SESSION_HPP

#include <QSharedPointer>

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
    
    QSharedPointer<rpgmapper::model::Atlas> atlas;
    QSharedPointer<rpgmapper::model::Map> currentMap;
    QSharedPointer<rpgmapper::model::Region> currentRegion;
    QSharedPointer<rpgmapper::model::ResourceDB> resourceDB;

public:
    
    /**
     * Constructor
     *
     * @param   parent      parent Qt object.
     */
    explicit Session(QObject * parent);
    
    /**
     * Destructor.
     */
    ~Session() override = default;
    
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
     * Gets the current selected Map of the current session.
     *
     * @return  the current selected map of the session.
     */
    QSharedPointer<rpgmapper::model::Map> & getCurrentMap() {
        return currentMap;
    }
    
    /**
     * Gets the current selected Map of the current session (const version).
     *
     * @return  the current selected map of the session.
     */
    QSharedPointer<rpgmapper::model::Map> const & getCurrentMap() const {
        return currentMap;
    }
    
    /**
     * Gets the current selected Region of the current session.
     *
     * @return  the current selected region of the session.
     */
    QSharedPointer<rpgmapper::model::Map> & getCurrentRegion() {
        return currentRegion;
    }
    
    /**
     * Gets the current selected Region of the current session (const version).
     *
     * @return  the current selected region of the session.
     */
    QSharedPointer<rpgmapper::model::Map> const & getCurrentRegion() const {
        return currentRegion;
    }

    /**
     * Selects a new current map.
     *
     * @param   map     the new selected map.
     */
    void selectMap(QSharedPointer<rpgmapper::model::Map> map);
    
    /**
     * Selects a new current map.
     *
     * @param   mapName     the name of the new selected map.
     */
    void selectMap(QString const & mapName);
    
    /**
     * Selects a new current region.
     *
     * @param   region  the new selected region.
     */
    void selectRegion(QSharedPointer<rpgmapper::model::Region> region);
    
    /**
     * Selects a new current region.
     *
     * @param   regionName      the name of the new selected map.
     */
    void selectRegion(QString const & regionName);

signals:
    
    /**
     * A new map has been selected.
     *
     * @param   mapName     the name of the new map selected.
     */
    void mapSelected(QString mapName);
    
    /**
     * A new region has been selected.
     *
     * @param   regionName  the name of the new region selected.
     */
    void regionSelected(QString regionName);
};


}
}


#endif

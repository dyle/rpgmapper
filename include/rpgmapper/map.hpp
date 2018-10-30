/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_MAP_HPP
#define RPGMAPPER_MODEL_MAP_HPP

#include <memory>

#include <QObject>
#include <QSize>
#include <QSharedPointer>
#include <QString>

#include <rpgmapper/json/json_io.hpp>
#include <rpgmapper/layer/layer_stack.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/resource_db.hpp>


namespace rpgmapper {
namespace model {


// TODO: why?
class Region;


/**
 * A single map.
 *
 * This is the heart of the rpgmapper. A map is a collection of layers,
 * which in turn define tiles, background, texts, etc. it has a name and
 * a coordinate system attached.
 */
class Map : public Nameable, public LayerStack {

    Q_OBJECT
    
    // TODO: turn to smart pointer
    CoordinateSystem * coordinateSystem;           /**< the coordinate system of the map */
    QString regionName;                            /**< The region the map is placed in. */

public:

    /**
     * Creates a map with a given name inside a region.
     *
     * @param   mapName         the new name of the map.
     * @param   regionName      the region to which the map belongs to.
     */
    explicit Map(QString mapName, QString regionName);

    /**
     * Destructor.
     */
    ~Map();
    
    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
     */
    bool applyJSON(QJsonObject const & json) override;
    
    /**
     * Suggests a new map name.
     *
     * @return  a name suitable for a new map.
     */
    static QString createNewMapName();
    
    /**
     * Gets the coordinate system of the map.
     *
     * @return  the coordinate system of the map.
     */
    CoordinateSystem * getCoordinateSystem() {
        return coordinateSystem;
    }
    
    /**
     * Gets the coordinate system of the map (const version).
     *
     * @return  the coordinate system of the map.
     */
    CoordinateSystem const * getCoordinateSystem() const {
        return coordinateSystem;
    }
    
    /**
     * Create a JSON structure from oourselves.
     *
     * @return      a valid JSON  structure from ooourselves.
     */
    QJsonObject getJSON() const override;

    /**
     * Gets the name of the region the map belongs to.
     *
     * @return  the region name the map belongs to.
     */
    QString getRegionName() const {
        return regionName;
    }
    
    /**
     * Checks if the given name is valid.
     *
     * @param   name        a potential name of a map.
     * @return  true, if the name can be used for a map.
     */
    static bool isNameValid(QString name);

    /**
     * Checks if this is a valid map.
     *
     * @return  returns true, if this is a valid map.
     */
    virtual bool isValid() const {
        return true;
    }

    /**
     * Returns the invalid null map pointer.
     *
     * [null object pattern]
     *
     * @return  an invalid null map.
     */
    static QSharedPointer<Map> const & null();
    
    /**
     * Sets a new name for the map.
     *
     * @param   name    a new name of this map.
     */
    void setName(QString name) override;
    
    /**
     * Sets a new region this map belongs to.
     *
     * @return  the new region of the map.
     */
    void setRegionName(QString regionName);
    
signals:
    
    /**
     * The map changed the region.
     */
    void changedRegion();
};


/**
 * An invalid Map.
 */
class InvalidMap final : public Map {

public:

    /**
     * Constructor.
     */
    InvalidMap()
        : Map{QString::Null{}, nullptr} {
    }

    /**
     * Checks if this is a valid map.
     *
     * @return  always false.
     */
    bool isValid() const override {
        return false;
    }
};


}
}


#endif

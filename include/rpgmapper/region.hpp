/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGION_HPP
#define RPGMAPPER_MODEL_REGION_HPP

#include <map>
#include <memory>
#include <set>

#include <QObject>
#include <QSharedPointer>

#include <rpgmapper/nameable.hpp>
#include <rpgmapper/maps.hpp>
#include <rpgmapper/region_pointer.hpp>


namespace rpgmapper {
namespace model {


/**
 * A Region is a collection of Maps.
 *
 * A region may only be created by Session object.
 */
class Region : public Nameable {

    Q_OBJECT

    Maps maps;            /**< All maps known to this region. */

public:

    /**
     * Constructor
     *
     * @param   name        name of the new region.
     */
    explicit Region(QString name);

    /**
     * Destructor.
     */
    ~Region() override = default;

    /**
     * Adds an existing map to this region.
     *
     * @param   map         the map to add.
     */
    void addMap(MapPointer map);
    
    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
     */
    bool applyJSON(QJsonObject const & json);
    
    /**
     * Create a JSON structure from oourselves.
     *
     * @return      a valid JSON  structure from ooourselves.
     */
    QJsonObject getJSON() const;
    
    /**
     * Gets a known map.
     *
     * @param   name        the map name.
     * @return  the map of this region with that name.
     */
    MapPointer getMap(QString name);
    
    /**
     * Gets a known map.
     *
     * @param   name        the map name.
     * @return  the map of this region with that name.
     */
    MapPointer const getMap(QString name) const;
    
    /**
     * Gets all maps known to this region.
     *
     * @return  all maps known to this region.
     */
    Maps const & getMaps() const {
        return maps;
    }
    
    /**
     * Checks if this is a valid region.
     *
     * @return  returns true, if this is a valid region.
     */
    virtual bool isValid() const {
        return true;
    }
    
    /**
     * Returns the invalid null region pointer.
     *
     * [null object pattern]
     *
     * @return  an invalid null region.
     */
    static RegionPointer const & null();

    /**
     * Removes a map from this region.
     *
     * @param   name        name of the map to remove.
     */
    void removeMap(QString name);

private:

    /**
     * Adds the maps defined in the given JSON array.
     *
     * @param   jsonArray       the array of maps
     */
    bool applyJSONMaps(QJsonArray const & jsonArray); 
    
signals:

    /**
     * We added a new map to this region.
     *
     * @param   name        name of the map added.
     */
    void mapAdded(QString name);
    
    /**
     * We removed a map from this region.
     *
     * @param   name        name of the map removed.
     */
    void mapRemoved(QString name);
};


/**
 * An invalid Region.
 */
class InvalidRegion final : public Region {

public:
    
    /**
     * Constructor.
     */
    InvalidRegion() : Region{QString::Null{}} {
    }
    
    /**
     * Checks if this is a valid region.
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

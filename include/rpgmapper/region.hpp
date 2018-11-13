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


namespace rpgmapper {
namespace model {


// fwd
class Session;


/**
 * A Region is a collection of Maps.
 *
 * A region may only be created by Session object.
 */
class Region : public Nameable {

    Q_OBJECT

    friend class rpgmapper::model::Session;
    
    std::set<QString> maps;             /**< All maps known to this region. */

public:

    /**
     * Destructor.
     */
    ~Region() override = default;

    /**
     * Adds an existing map to this region.
     *
     * @param   name        name of the map to add.
     */
    void addMap(QString name);
    
    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
     */
    bool applyJSON(QJsonObject const & json);
    
    /**
     * Change the name of a map known to this region.
     *
     * @param   oldName     old name of the map
     * @param   newName     new name of the map
     */
    void changeMapName(QString oldName, QString newName);
    
    /**
     * Checks if the given map name is part of this region.
     *
     * @param   map     the nam eof the mpa to check.
     * @return  returns true, if the given map belongs to this region.
     */
    bool containsMap(QString map) const;
    
    /**
     * Suggests a new region name.
     *
     * @return  a new proper name of a region.
     */
    static QString createRegionName();
    
    /**
     * Create a JSON structure from oourselves.
     *
     * @return      a valid JSON  structure from ooourselves.
     */
    QJsonObject getJSON() const;

    /**
     * Gets all maps known to this region.
     *
     * @return  all maps known to this region.
     */
    std::set<QString> const & getMapNames() const {
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
    static QSharedPointer<rpgmapper::model::Region> const & null();

    /**
     * Removes a map from this region.
     *
     * @param   name        name of the map to remove.
     */
    void removeMap(QString name);

    
    /**
     * Sets a new name for this region.
     *
     * @param   name        the new name of this region.
     */
    void setName(QString name) override;

protected:

    /**
     * Constructor
     *
     * @param   name        name of the new region.
     */
    explicit Region(QString name);

private:

    /**
     * Applies a JSON Map info to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
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
    InvalidRegion()
        : Region{QString::Null{}} {
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

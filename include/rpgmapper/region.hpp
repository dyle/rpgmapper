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

#include <rpgmapper/map.hpp>
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/resource_db.hpp>


namespace rpgmapper {
namespace model {


/**
 * A Region is a collection of Maps.
 */
class Region : public Nameable {

    Q_OBJECT

    std::set<QString> maps;             /**< All maps known to this region. */

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
    ~Region() = default;

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

private slots:

    /**
     * A map of us has changed its name.
     *
     * @param   nameBefore      name of the map as we know it
     * @param   nameAfter       name of the map afterwards.
     */
    void changedMapName(QString nameBefore, QString nameAfter);

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

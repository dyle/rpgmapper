/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_ATLAS_HPP
#define RPGMAPPER_MODEL_ATLAS_HPP

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include <rpgmapper/atlas_pointer.hpp>
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/region_pointer.hpp>
#include <rpgmapper/regions.hpp>
#include <rpgmapper/resource/resource_collection_pointer.hpp>


namespace rpgmapper::model {


/**
 * This is an atlas as a set of regions, each with a set of maps.
 */
class Atlas : public Nameable {

    Q_OBJECT
    
    Regions regions;                /**< The regions of the atlas. */
    
    /**
     * The local resources in this atlas.
     */
    rpgmapper::model::resource::ResourceCollectionPointer resources;

public:

    /**
     * Constructor
     *
     * @param   name        the name of the atlas.
     */
    explicit Atlas(QString name = QString::null);
    
    /**
     * Adds an existing region to the atlas.
     *
     * @param   region      the region to add.
     */
    void addRegion(RegionPointer region);

    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     */
    void applyJson(QJsonObject const & json) override;
    
    /**
     * Create a JSON structure from ourselves.
     *
     * @return      a valid JSON  structure from ourselves.
     */
    QJsonObject getJson() const override;
    
    /**
     * Gets a known region.
     *
     * @param   name        the region name.
     * @return  the region of this region with that name.
     */
    RegionPointer getRegion(QString name);
    
    /**
     * Gets a known region.
     *
     * @param   name        the region name.
     * @return  the region of this region with that name.
     */
    RegionPointer const getRegion(QString name) const;
    
    /**
     * Gets all regions known to this region.
     *
     * @return  all regions known to this region.
     */
    Regions const & getRegions() const {
        return regions;
    }
    
    /**
     * Returns the resources local to this atlas.
     *
     * @return  the resources used in this atlas.
     */
    rpgmapper::model::resource::ResourceCollectionPointer & getResources() {
        return resources;
    }
    
    /**
     * Returns the resources local to this atlas (const version).
     *
     * @return  the resources used in this atlas.
     */
    rpgmapper::model::resource::ResourceCollectionPointer const & getResources() const {
        return resources;
    }
    
    /**
     * Checks if this is a valid atlas.
     *
     * @return  returns true, if this is a valid atlas.
     */
    virtual bool isValid() const {
        return true;
    }
    
    /**
     * Returns the invalid null atlas pointer.
     *
     * [null object pattern]
     *
     * @return  an invalid null atlas.
     */
    static AtlasPointer const & null();
    
    /**
     * Removes a region from this region.
     *
     * @param   name        name of the region to remove.
     */
    void removeRegion(QString name);
    
private:
    
    /**
     * Applies the regions found in a JSON.
     *
     * Note: previous regions will be removed.
     *
     * @param   json        the JSON holding the regions.
     */
    void applyJsonRegions(QJsonValue const & json);

private slots:
    
    /**
     * The name of a region changed.
     *
     * @param   oldName     the old name
     * param    newName     the new name
     */
    void regionNameChanged(QString oldName, QString newName);
    
signals:
    
    /**
     * Added a mape to the atlas.
     *
     * @param   name        name of the map added.
     */
    void mapAdded(QString name);
    
    /**
     * Removed a map from the atlas.
     *
     * @param   name        name of the map removed.
     */
    void mapRemoved(QString name);
    
    /**
     * Added a region to the atlas.
     *
     * @param   name        name of the region added.
     */
    void regionAdded(QString name);
    
    /**
     * Removed a region from the atlas.
     *
     * @param   name        name of the region removed.
     */
    void regionRemoved(QString name);
};


/**
 * An invalid Atlas.
 */
class InvalidAtlas final : public Atlas {

public:
    
    /**
     * Constructor.
     */
    InvalidAtlas() : Atlas{nullptr} {
    }
    
    /**
     * Checks if this is a valid atlas.
     *
     * @return  always false.
     */
    bool isValid() const override {
        return false;
    }
};


}


#endif
